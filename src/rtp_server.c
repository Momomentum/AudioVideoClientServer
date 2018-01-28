#include <gst/gst.h>
#include <gio/gio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

#define BLOCK_SIZE 1024
#define PORT 2345


typedef struct _AudioData {
    GstElement *audiobin;
    GstElement *decoder;
    GstElement *src;
    GstElement *convert;
    GstElement *volume;
    GstElement *sink;
    GstElement *payload;
    GstElement *pipeline;
} AudioData;


typedef struct _CustomData {
    AudioData *left_audio;
    AudioData *right_audio;
} CustomData;



typedef struct _ConnData {
    GSocketConnection *connection;
    CustomData *data;
    char message[BLOCK_SIZE];
} ConnData;


void message_ready (GObject * source_object,
                    GAsyncResult *res,
                    gpointer user_data)
{
    GInputStream *istream = G_INPUT_STREAM (source_object);
    GError *error = NULL;
    ConnData *data = user_data;

    long count;

    count = g_input_stream_read_finish (istream,
                                        res,
                                        &error);

    if (count == -1) {
        g_error ("Error when receiving message");
        if (error != NULL) {
            g_error ("%s", error->message);
            g_clear_error (&error);
        }
    }

    if(strcmp(data->message, "init") == 0) {
        GSocketAddress *sockAdd =g_socket_connection_get_remote_address(data->connection, NULL);
        GInetAddress *inet_address = g_object_ref(g_inet_socket_address_get_address(G_INET_SOCKET_ADDRESS(sockAdd)));
        gchar *ip_addr = g_inet_address_to_string(inet_address);

        g_object_set(data->data->left_audio->sink, "host", ip_addr);
        g_object_set(data->data->right_audio->sink, "host", ip_addr);

        g_message ("Message was: \"%s\"\n", ip_addr);
        g_free(ip_addr);
        g_object_unref(sockAdd);
    } else {
        const cJSON *control = NULL;
        const cJSON *control_value = NULL;
        const cJSON *target = NULL;


        cJSON *parsedMessage = cJSON_Parse(data->message);
        if(parsedMessage == NULL) {
            g_message("Could not parse json");
        } else {
            control = cJSON_GetObjectItemCaseSensitive(parsedMessage, "control");
            control_value = cJSON_GetObjectItemCaseSensitive(parsedMessage, "value");
            target = cJSON_GetObjectItemCaseSensitive(parsedMessage, "target");
            if (cJSON_IsString(control) && (control->valuestring != NULL)) {
//                g_message("Control: \"%s\"\n", control->valuestring);
                if (strcmp(control->valuestring, "volume") == 0) {
                    if(strcmp(target->valuestring, "audio_1") == 0) {
//                        g_message("Volume: \"%f\"\n", atof(control_value->valuestring));
                        double vol = atof(control_value->valuestring);
                        g_object_set(data->data->left_audio->volume, "volume", vol, NULL);
                    }
                    else if(strcmp(target->valuestring, "audio_2") == 0) {
                        double vol = atof(control_value->valuestring);
                        g_object_set(data->data->right_audio->volume, "volume", vol, NULL);
                    }
//                    g_message("Volume: \"%s\"\n", control_value->valuestring);
//                    g_message("Target: \"%s\"\n", target->valuestring);
                } else if (strcmp(control->valuestring, "eq") == 0) {
                    const cJSON *low, *mid, *high = NULL;
                    low = cJSON_GetObjectItemCaseSensitive(control_value, "low");
                    mid = cJSON_GetObjectItemCaseSensitive(control_value, "mid");
                    high = cJSON_GetObjectItemCaseSensitive(control_value, "high");
                    g_message("Low: \"%s\"\n", low->valuestring);
                    g_message("Mid: \"%s\"\n", mid->valuestring);
                    g_message("High: \"%s\"\n", high->valuestring);
                    g_message("Target: \"%s\"\n", target->valuestring);
                } else if (strcmp(control->valuestring, "play") == 0) {
                    if(strcmp(target->valuestring, "audio_1") == 0) {
                        if(strcmp(control_value->valuestring, "1") == 0) {
                            gst_element_set_state (data->data->left_audio->pipeline, GST_STATE_PLAYING);
                        }
                        else if(strcmp(control_value->valuestring, "0") == 0) {
                            gst_element_set_state (data->data->left_audio->pipeline, GST_STATE_PAUSED);
                        }
                    }
                    else if(strcmp(target->valuestring, "audio_2") == 0) {
                        if(strcmp(control_value->valuestring, "1") == 0) {
                            gst_element_set_state (data->data->right_audio->pipeline, GST_STATE_PLAYING);
                        }
                        else if(strcmp(control_value->valuestring, "0") == 0) {
                            gst_element_set_state (data->data->right_audio->pipeline, GST_STATE_PAUSED);
                        }
                    }
                    g_message("Play: \"%s\"\n", control_value->valuestring);
                    g_message("Target: \"%s\"\n", target->valuestring);
                }
            }
        }
        cJSON_Delete(parsedMessage);
    }


    g_object_unref (G_SOCKET_CONNECTION (data->connection));
    g_free (data);
}

static gboolean
incoming_callback (GSocketService *service,
                   GSocketConnection * connection,
                   GObject * source_object,
                   CustomData *data)
{
    g_message ("Received Connection from client!\n");
    GInputStream *istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));

    ConnData *stream_data = g_new (ConnData, 1);

    stream_data->connection = g_object_ref (connection);
    stream_data->data = data;

    g_input_stream_read_async (istream,
                               stream_data->message,
                               sizeof (stream_data->message),
                               G_PRIORITY_DEFAULT,
                               NULL,
                               message_ready,
                               stream_data);
    return FALSE; // TODO check if should return true
}



static gboolean
my_bus_callback (GstBus     *bus,
                 GstMessage *message,
                 gpointer    data)
{
    g_print ("Got %s message\n", GST_MESSAGE_TYPE_NAME (message));

    switch (GST_MESSAGE_TYPE (message)) {
        case GST_MESSAGE_ERROR: {
            GError *err;
            gchar *debug;

            gst_message_parse_error (message, &err, &debug);
            g_print ("Error: %s\n", err->message);
            g_error_free (err);
            g_free (debug);

            g_main_loop_quit (data);
            break;
        }
        case GST_MESSAGE_EOS:
            /* end-of-stream */
            g_main_loop_quit (data);
            break;
        default:
            /* unhandled message */
            break;
    }

    /* we want to be notified again the next time there is a message
     * on the bus, so returning TRUE (FALSE means we want to stop watching
     * for messages on the bus and our callback should not be called again)
     */
    return TRUE;
}



//GstElement *pipeline, *audio;

static void
cb_newpad (GstElement *decodebin,
           GstPad     *pad,
           AudioData *data)
{
    GstCaps *caps;
    GstStructure *str;
    GstPad *audiopad;
    GstPadLinkReturn ret;
    const gchar *new_pad_type = NULL;

    /* only link once */
    audiopad = gst_element_get_static_pad (data->audiobin, "sink");
    if (GST_PAD_IS_LINKED (audiopad)) {
        g_object_unref (audiopad);
        return;
    }

    /* check media type */
    caps = gst_pad_query_caps (pad, NULL);
    str = gst_caps_get_structure (caps, 0);
    new_pad_type = gst_structure_get_name (str);
    if (!g_strrstr (gst_structure_get_name (str), "audio/x-raw")) {
//        gst_println(gst_structure_get_name (str));
        gst_caps_unref (caps);
        gst_object_unref (audiopad);
        return;
    }
    gst_caps_unref (caps);

    /* Attempt the link */
    ret = gst_pad_link (pad, audiopad);
    if (GST_PAD_LINK_FAILED (ret)) {
        g_print ("  Type is '%s' but link failed.\n", new_pad_type);
    } else {
        g_print ("  Link succeeded (type '%s').\n", new_pad_type);
    }
    g_object_unref (audiopad);
}

gint
main (gint   argc,
      gchar *argv[])
{
    GMainLoop *loop;
    //GstElement *src, *dec, *conv, *volume,*sink, *payload;


    AudioData audio_left;
    AudioData audio_right;


    CustomData data;

    data.left_audio = &audio_left;
    data.right_audio = &audio_right;

    GstBus *bus1;
    GstBus *bus2;
    GstBus *bus3;

    /* init GStreamer */
    gst_init (&argc, &argv);
    loop = g_main_loop_new (NULL, FALSE);


    // TCP Server

    GSocketService *service;
    GError *error = NULL;
    gboolean ret;

    service = g_socket_service_new ();
    ret = g_socket_listener_add_inet_port (G_SOCKET_LISTENER (service),
                                           PORT, NULL, &error);

    if (ret && error != NULL)
    {
        g_error ("%s", error->message);
        g_clear_error (&error);
        return 1;
    }

    g_signal_connect (service,
                      "incoming",
                      G_CALLBACK (incoming_callback),
                      &data);

    g_socket_service_start (service);


    // Gstreamer

    /* setup */
    audio_left.pipeline = gst_pipeline_new ("pipeline_left");
    audio_right.pipeline = gst_pipeline_new ("pipeline_right");
//    convert = gst_element_factory_make("audioconvert", "audioconvert");


    // Audio left
    audio_left.src = gst_element_factory_make ("filesrc", "src_left");
    g_object_set (G_OBJECT (audio_left.src), "location", "/home/moritzmg/Music/output.mp3", NULL);
    audio_left.decoder = gst_element_factory_make ("decodebin", "decoder_left");
    gst_bin_add_many (GST_BIN (audio_left.pipeline), audio_left.src, audio_left.decoder, NULL);
    gst_element_link (audio_left.src, audio_left.decoder);

    /* create audio output */
    audio_left.audiobin = gst_bin_new("audiobin_left");
    audio_left.volume = gst_element_factory_make("volume", "vol_left");
    audio_left.convert = gst_element_factory_make ("audioconvert", "convert_left");
    audio_left.payload = gst_element_factory_make ("rtpL16pay", "pay_left");
    audio_left.sink = gst_element_factory_make ("udpsink", "sink_left");

    g_object_set (audio_left.sink, "host", "127.0.0.1", "port", 3001, NULL);


    gst_bin_add_many(GST_BIN(audio_left.audiobin), audio_left.volume, audio_left.convert, audio_left.payload, audio_left.sink, NULL);

    gst_element_link_many(audio_left.volume, audio_left.convert, audio_left.payload, audio_left.sink, NULL);

    GstPad *audiopad_left = gst_element_get_static_pad(audio_left.volume, "sink");
    gst_element_add_pad(audio_left.audiobin, gst_ghost_pad_new("sink", audiopad_left));
    gst_object_unref(audiopad_left);

    gst_bin_add(GST_BIN(audio_left.pipeline), audio_left.audiobin);
//    g_object_set (audio_left.volume, "volume", 1.0, "mute", FALSE, NULL);

    g_signal_connect (audio_left.decoder, "pad-added", G_CALLBACK (cb_newpad), &audio_left);




    // Gstreamer

    /* setup */
//    convert = gst_element_factory_make("audioconvert", "audioconvert");


    // Audio right
    audio_right.src = gst_element_factory_make ("filesrc", "src_right");
    g_object_set (G_OBJECT (audio_right.src), "location", "/home/moritzmg/Music/bensound-happyrock.mp3", NULL);
    audio_right.decoder = gst_element_factory_make ("decodebin", "decoder_right");
    gst_bin_add_many (GST_BIN (audio_right.pipeline), audio_right.src, audio_right.decoder, NULL);
    gst_element_link (audio_right.src, audio_right.decoder);

    /* create audio output */
    audio_right.audiobin = gst_bin_new("audiobin_right");
    audio_right.volume = gst_element_factory_make("volume", "vol_right");
    audio_right.convert = gst_element_factory_make ("audioconvert", "convert_right");
    audio_right.payload = gst_element_factory_make ("rtpL16pay", "pay_right");
    audio_right.sink = gst_element_factory_make ("udpsink", "sink_right");

    g_object_set (audio_right.sink, "host", "127.0.0.1", "port", 3002, NULL);


    gst_bin_add_many(GST_BIN(audio_right.audiobin), audio_right.volume, audio_right.convert, audio_right.payload, audio_right.sink, NULL);

    gst_element_link_many(audio_right.volume, audio_right.convert, audio_right.payload, audio_right.sink, NULL);

    GstPad *audiopad_right = gst_element_get_static_pad(audio_right.volume, "sink");
    gst_element_add_pad(audio_right.audiobin, gst_ghost_pad_new("sink", audiopad_right));
    gst_object_unref(audiopad_right);

    gst_bin_add(GST_BIN(audio_right.pipeline), audio_right.audiobin);

    g_signal_connect (audio_right.decoder, "pad-added", G_CALLBACK (cb_newpad), &audio_right);




    bus1 = gst_pipeline_get_bus (GST_PIPELINE (audio_left.pipeline));
    gst_bus_add_watch (bus1, my_bus_callback, loop);
    gst_object_unref (bus1);

    bus2 = gst_pipeline_get_bus (GST_PIPELINE (audio_right.pipeline));
    gst_bus_add_watch (bus2, my_bus_callback, loop);
    gst_object_unref (bus2);


    /* run */
    gst_element_set_state (audio_left.pipeline, GST_STATE_PAUSED);
    gst_element_set_state (audio_right.pipeline, GST_STATE_PAUSED);

    g_main_loop_run (loop);

    /* cleanup */
//    g_socket_service_stop (service);
    gst_element_set_state (audio_left.pipeline, GST_STATE_NULL);
    gst_element_set_state (audio_right.pipeline, GST_STATE_NULL);
    gst_object_unref (GST_OBJECT (audio_left.pipeline));
    gst_object_unref (GST_OBJECT (audio_right.pipeline));


    return 0;
}
