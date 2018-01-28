#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include <gst/gst.h>



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
    GstElement *mixed_audio_pipeline;
//    GstElement *mixed_audio_dec;
    GstElement *mixed_audio_depay;
    GstElement *mixed_audio_src;
    GstElement *mixed_audio_sink;


} CustomData;

#endif // CUSTOMDATA_H
