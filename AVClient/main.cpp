#include "mainwindow.h"
#include <QApplication>

#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QTimer>
#include <QWidget>


typedef struct _CustomData {
    GstElement *pipeline;
    GstElement *decodebin;
    GstElement *video_dec;
    GstElement *depay;
    GstElement *src;
    GstElement *sink;
} CustomData;

static void
cb_newpad (GstElement *decodebin,
           GstPad     *pad,
           CustomData *data)
{
    GstCaps *caps;
    GstStructure *str;
    GstPad *videopad;
    GstPadLinkReturn ret;
    const gchar *new_pad_type = NULL;

    qDebug() << "adsadsadas";

    /* only link once */
    videopad = gst_element_get_static_pad (data->sink, "sink");
    if (GST_PAD_IS_LINKED (videopad)) {
        g_object_unref (videopad);
        return;
    }

    /* check media type */
    caps = gst_pad_query_caps (pad, NULL);
    str = gst_caps_get_structure (caps, 0);
    new_pad_type = gst_structure_get_name (str);
    if (!g_strrstr (gst_structure_get_name (str), "video/x-raw")) {
//        gst_println(gst_structure_get_name (str));
        qDebug() << gst_structure_get_name (str);
        gst_caps_unref (caps);
        gst_object_unref (videopad);
        return;
    }
    gst_caps_unref (caps);

    /* Attempt the link */
    ret = gst_pad_link (pad, videopad);
    if (GST_PAD_LINK_FAILED (ret)) {
        g_print ("  Type is '%s' but link failed.\n", new_pad_type);
    } else {
        qDebug() << "  Link succeeded type: " << new_pad_type;

//        g_print ("  Link succeeded (type '%s').\n", new_pad_type);
    }

    g_object_unref (videopad);
}



int main(int argc, char *argv[])
{
    gst_init (&argc, &argv);

    QApplication a(argc, argv);
    MainWindow w;

    CustomData data;

    /* prepare the pipeline */

    qDebug() << "Preparing Pipeline";

    data.pipeline = gst_pipeline_new("xoverlay");
    data.src = gst_element_factory_make("udpsrc", "src");
    data.decodebin = gst_element_factory_make("decodebin", "decodebin");
    data.depay = gst_element_factory_make("rtph264depay", "depay");
    data.video_dec = gst_element_factory_make("avdec_h264", "videodec");
    data.sink = gst_element_factory_make("xvimagesink", "x_sink");

    GstCaps *caps = gst_caps_new_simple("application/x-rtp",
                                        "media", G_TYPE_STRING, "video",
                                        "clock-rate", G_TYPE_INT, 90000,
                                        "encoding-name", G_TYPE_STRING, "H264",
                                        "payload", G_TYPE_INT, 96,
                                        NULL
                                        );

    g_object_set(G_OBJECT(data.src), "uri", "udp://127.0.0.1", NULL);
    g_object_set(G_OBJECT(data.src), "port", 3000, NULL);
    g_object_set(G_OBJECT(data.src), "caps", caps, NULL);
    gst_caps_unref(caps);

//    GstElement *pipeline = gst_pipeline_new ("xvoverlay");
//    GstElement *src = gst_element_factory_make ("udpsrc", NULL);
//    GstElement *decodebin = gst_element_factory_make ("decodebin", NULL);
//    GstElement *depay = gst_element_factory_make("vp8depay", NULL);
//    GstElement *sink = gst_element_factory_make("xvimagesink", NULL);

//    g_object_set(src, "uri", "file:///home/moritzmg/Videos/BigBuckBunny_512kb.mp4", NULL);

    if (data.sink == NULL)
      g_error ("Couldn't find a working video sink.");

//    g_signal_connect (data.decodebin, "pad-added", G_CALLBACK (cb_newpad), &data);

//    gst_bin_add_many (GST_BIN (data.pipeline), data.src, data.decodebin, NULL);
    gst_bin_add_many (GST_BIN (data.pipeline), data.src, data.depay, data.video_dec, data.sink, NULL);

    gst_element_link(data.src, data.depay);
    gst_element_link(data.depay, data.video_dec);
    gst_element_link(data.video_dec, data.sink);

//    gst_element_link(data.src, data.decodebin);

//    gst_bin_add_many (GST_BIN (pipeline), src, sink, NULL);
//    gst_element_link (src, sink);



    QWidget *widget = w.findChild<QWidget*>("widget");
    Q_ASSERT(widget);
    WId xwinid = widget->winId();
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data.sink), xwinid);

    /* run the pipeline */

    GstStateChangeReturn sret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
    if (sret == GST_STATE_CHANGE_FAILURE) {
      gst_element_set_state (data.pipeline, GST_STATE_NULL);
      gst_object_unref (data.pipeline);
      /* Exit application */
      QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
    }

    w.show();
    int ret = a.exec();

//    widget->hide();
    gst_element_set_state (data.pipeline, GST_STATE_NULL);
    gst_object_unref (data.pipeline);

    return ret;

    ////////////////////


//    w.show();

//    return a.exec();
}
