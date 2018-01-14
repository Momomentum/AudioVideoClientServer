cmake_minimum_required(VERSION 3.3)
project(gst_RTSP_server C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED) 
pkg_check_modules(GSTREAMER
    REQUIRED gstreamer-1.0) 
pkg_check_modules(GSTRTSP REQUIRED gstreamer-rtsp-server-1.0)

set(SOURCE_FILES src/rtsp_serv.c src/GstRtspMediaFactoryCustom.c src/GstRtspMediaFactoryCustom.h)
add_executable(gst_RTSP_server ${SOURCE_FILES}) 

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(${GSTREAMER_INCLUDE_DIRS})
include_directories(${GSTRTSP_INCLUDE_DIRS})

target_compile_options(gst_RTSP_server PUBLIC ${GLIB_CFLAGS_OTHER})
target_compile_options(gst_RTSP_server PUBLIC ${GSTREAMER_CFLAGS_OTHER})
target_compile_options(gst_RTSP_server PUBLIC ${GSTRTSP_CFLAGS_OTHER})

target_link_libraries(gst_RTSP_server ${GLIB_LIBRARIES}) 
target_link_libraries(gst_RTSP_server ${GSTREAMER_LIBRARIES}) 
target_link_libraries(gst_RTSP_server ${GSTRTSP_LIBRARIES})
