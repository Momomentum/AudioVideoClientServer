#include <gst/gst.h>
#include <gio/gio.h>
#include "cJSON.h"

#define BLOCK_SIZE 1024
#define PORT 2345


typedef struct _CustomData {
    GstElement *pipeline;
    GstElement *decoder;
    GstElement *src;


    GstElement *audiobin;
    GstElement *convert;
    GstElement *volume;
    GstElement *sink;
    GstElement *payload;
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

//    cJSON *parsedMessage = cJSON_Parse(data->message);
//    if(parsedMessage == NULL) {
//        g_error ("Could not parse json");
//    } else {
//        g_object_set(data->data->volume, "volume", 0, NULL);
//    }

    g_message ("Message was: \"%s\"\n", data->message);
    g_object_unref (G_SOCKET_CONNECTION (data->connection));
    g_free (data);
//    cJSON_Delete(parsedMessage);
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
           CustomData *data)
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

//
//    /* link'n'play */
//    gst_pad_link (pad, audiopad);

    g_object_unref (audiopad);
}

gint
main (gint   argc,
      gchar *argv[])
{
    GMainLoop *loop;
    //GstElement *src, *dec, *conv, *volume,*sink, *payload;


    CustomData data;

    GstPad *audiopad;
    GstBus *bus;

    /* init GStreamer */
    gst_init (&argc, &argv);
    loop = g_main_loop_new (NULL, FALSE);

    /* make sure we have input */
    if (argc != 2) {
        g_print ("Usage: %s <filename>\n", argv[0]);
        return -1;
    }


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
    data.pipeline = gst_pipeline_new ("pipeline");

    bus = gst_pipeline_get_bus (GST_PIPELINE (data.pipeline));
    gst_bus_add_watch (bus, my_bus_callback, loop);
    gst_object_unref (bus);

    data.src = gst_element_factory_make ("filesrc", "source");
    g_object_set (G_OBJECT (data.src), "location", argv[1], NULL);
    data.decoder = gst_element_factory_make ("decodebin", "decoder");
    g_signal_connect (data.decoder, "pad-added", G_CALLBACK (cb_newpad), &data);
    gst_bin_add_many (GST_BIN (data.pipeline), data.src, data.decoder, NULL);
    gst_element_link (data.src, data.decoder);

    /* create audio output */
    data.audiobin = gst_bin_new ("audiobin");
    data.volume = gst_element_factory_make("volume", "vol");
    data.convert = gst_element_factory_make ("audioconvert", "aconv");

    audiopad = gst_element_get_static_pad (data.volume, "sink");
    data.payload = gst_element_factory_make ("rtpL16pay", "payload");
    data.sink = gst_element_factory_make ("udpsink", "sink");


    g_object_set (data.volume, "volume", 1.0, "mute", FALSE, NULL);
    g_object_set (data.sink, "host", "127.0.0.1", "port", 3000, NULL);
//    g_object_set (G_OBJECT (payload), "channels", 2, NULL);

    //sink = gst_element_factory_make ("alsasink", "sink");
    gst_bin_add_many (GST_BIN (data.audiobin), data.volume, data.convert, data.payload, data.sink, NULL);
    gst_element_link (data.volume, data.convert);
    gst_element_link (data.convert, data.payload);
//    gst_element_link(data.convert, data.payload);
    gst_element_link (data.payload, data.sink);
    gst_element_add_pad (data.audiobin, gst_ghost_pad_new ("sink", audiopad));

    gst_object_unref (audiopad);
    gst_bin_add (GST_BIN (data.pipeline), data.audiobin);

    /* run */
    gst_element_set_state (data.pipeline, GST_STATE_PLAYING);

    g_main_loop_run (loop);

    /* cleanup */
    g_socket_service_stop (service);
    gst_element_set_state (data.pipeline, GST_STATE_NULL);
    gst_object_unref (GST_OBJECT (data.pipeline));

    return 0;
}
