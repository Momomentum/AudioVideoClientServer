#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>





int main (int argc, char *argv[])
{
    GMainLoop *loop;
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *videoFactory;
    GstRTSPMediaFactory *audioFactory;


    gst_init (&argc, &argv);

    loop = g_main_loop_new (NULL, FALSE);

    /* create a server instance */
    server = gst_rtsp_server_new ();

    /* get the mount points for this server, every server has a default object
     * that be used to map uri mount points to media factories */
    mounts = gst_rtsp_server_get_mount_points (server);

    /* make a media videoFactory for a test stream. The default media videoFactory can use
     * gst-launch syntax to create pipelines. 
     * any launch line works as long as it contains elements named pay%d. Each
     * element with pay%d names will be a stream */
    videoFactory = gst_rtsp_media_factory_new ();
    audioFactory = gst_rtsp_media_factory_new ();

    gst_rtsp_media_factory_set_launch (videoFactory,
            "( filesrc location=/home/moritzmg/Videos/BigBuckBunny_512kb.mp4 ! decodebin ! x264enc ! rtph264pay pt=96 name=pay0 )");

    gst_rtsp_media_factory_set_shared (videoFactory, TRUE);
    gst_rtsp_media_factory_set_latency(videoFactory, 200);



    /* attach the test videoFactory to the /test url */
    gst_rtsp_mount_points_add_factory (mounts, "/test", videoFactory);


    // Audio
    gst_rtsp_media_factory_set_launch (audioFactory,
                                       "( filesrc location=/home/moritzmg/Music/output.wav ! decodebin ! audioconvert ! rtpL16pay name=pay0 )");
//                                       "( audiotestsrc freq=1000 ! audioconvert ! rtpL16pay name=pay0 )");

    gst_rtsp_media_factory_set_shared (audioFactory, TRUE);
    gst_rtsp_media_factory_set_latency(audioFactory, 200);

    /* attach the test audioFactory to the /test url */
    gst_rtsp_mount_points_add_factory (mounts, "/audio1", audioFactory);


    /* don't need the ref to the mapper anymore */
    g_object_unref (mounts);

    /* attach the server to the default maincontext */
    gst_rtsp_server_attach (server, NULL);

    /* start serving */
    g_print ("stream ready at rtsp://127.0.0.1:8554/test\n");
    g_print ("stream ready at rtsp://127.0.0.1:8554/audio1\n");
    g_main_loop_run (loop);

    return 0;
}
