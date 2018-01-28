#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include <gst/gst.h>
#include <glib.h>



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
    GstElement *left_audio_pipeline;
//    GstElement *left_audio_dec;
    GstElement *left_audio_depay;
    GstElement *left_audio_src;
    GstElement *left_audio_sink;

    GstElement *right_audio_pipeline;
//    GstElement *right_audio_dec;
    GstElement *right_audio_depay;
    GstElement *right_audio_src;
    GstElement *right_audio_sink;


} CustomData;

#endif // CUSTOMDATA_H
