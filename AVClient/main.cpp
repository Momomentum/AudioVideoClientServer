#include "mainwindow.h"
#include <QApplication>

#include <glib.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>
#include <QTimer>
#include <QWidget>


typedef struct _CustomData {
    // Video1 data
    GstElement *video1_pipeline;
    GstElement *video1_dec;
    GstElement *video1_depay;
    GstElement *video1_src;
    GstElement *video1_sink;

    // Video2 data
    GstElement *video2_pipeline;
    GstElement *video2_dec;
    GstElement *video2_depay;
    GstElement *video2_src;
    GstElement *video2_sink;

    // MixedVideo data
    GstElement *mixed_video_pipeline;
    GstElement *mixed_video_dec;
    GstElement *mixed_video_depay;
    GstElement *mixed_video_src;
    GstElement *mixed_video_sink;

    // Audio Data


} CustomData;


int main(int argc, char *argv[])
{
    gst_init (&argc, &argv);

    QApplication a(argc, argv);
    MainWindow w;

    CustomData data;

    /* prepare the pipeline */

    qDebug() << "Preparing Pipeline";

    data.video1_pipeline = gst_pipeline_new("xoverlay");
    data.video1_src = gst_element_factory_make("udpsrc", "src");
    data.video1_depay = gst_element_factory_make("rtph264depay", "depay");
    data.video1_dec = gst_element_factory_make("avdec_h264", "videodec");
    data.video1_sink = gst_element_factory_make("xvimagesink", "x_sink");

    GstCaps *caps = gst_caps_new_simple("application/x-rtp",
                                        "media", G_TYPE_STRING, "video",
                                        "clock-rate", G_TYPE_INT, 90000,
                                        "encoding-name", G_TYPE_STRING, "H264",
                                        "payload", G_TYPE_INT, 96,
                                        NULL
                                        );

    g_object_set(G_OBJECT(data.video1_src), "uri", "udp://127.0.0.1", NULL);
    g_object_set(G_OBJECT(data.video1_src), "port", 3000, NULL);
    g_object_set(G_OBJECT(data.video1_src), "caps", caps, NULL);
    gst_caps_unref(caps);


    if (data.video1_sink == NULL)
      g_error ("Couldn't find a working video sink.");

    gst_bin_add_many (GST_BIN (data.video1_pipeline), data.video1_src, data.video1_depay, data.video1_dec, data.video1_sink, NULL);

    gst_element_link(data.video1_src, data.video1_depay);
    gst_element_link(data.video1_depay, data.video1_dec);
    gst_element_link(data.video1_dec, data.video1_sink);




    QWidget *widget = w.findChild<QWidget*>("widget");
    Q_ASSERT(widget);
    WId xwinid = widget->winId();
    gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data.video1_sink), xwinid);

    /* run the pipeline */

    GstStateChangeReturn sret = gst_element_set_state (data.video1_pipeline, GST_STATE_PLAYING);
    if (sret == GST_STATE_CHANGE_FAILURE) {
      gst_element_set_state (data.video1_pipeline, GST_STATE_NULL);
      gst_object_unref (data.video1_pipeline);
      /* Exit application */
      QTimer::singleShot(0, QApplication::activeWindow(), SLOT(quit()));
    }

    w.show();
    int ret = a.exec();

//    widget->hide();
    gst_element_set_state (data.video1_pipeline, GST_STATE_NULL);
    gst_object_unref (data.video1_pipeline);

    return ret;

    ////////////////////


//    w.show();

//    return a.exec();
}
