cmake_minimum_required(VERSION 3.3)
project(rtp_server C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindPkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED) 
pkg_check_modules(GSTREAMER
    REQUIRED gstreamer-1.0)
pkg_check_modules(GIO gio-unix-2.0)
#pkg_check_modules(GSTRTSP REQUIRED gstreamer-rtsp-server-1.0)

set(SOURCE_FILES src/rtp_server.c src/cJSON.c)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


include_directories(${GLIB_INCLUDE_DIRS})
include_directories(${GSTREAMER_INCLUDE_DIRS})
include_directories(${GIO_INCLUDE_DIRS})
#include_directories(${GSTRTSP_INCLUDE_DIRS})

target_compile_options(${PROJECT_NAME} PUBLIC ${GLIB_CFLAGS_OTHER})
target_compile_options(${PROJECT_NAME} PUBLIC ${GSTREAMER_CFLAGS_OTHER})
target_compile_options(${PROJECT_NAME} PUBLIC ${GIO_CFLAGS_OTHER})
#target_compile_options(gst_RTSP_server PUBLIC ${GSTRTSP_CFLAGS_OTHER})

target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GIO_LIBRARIES})
#target_link_libraries(gst_RTSP_server ${GSTRTSP_LIBRARIES})


add_executable(test_client src/test_client.c src/cJSON.c)
target_compile_options(test_client PUBLIC ${GLIB_CFLAGS_OTHER})
target_compile_options(test_client PUBLIC ${GIO_CFLAGS_OTHER})
target_link_libraries(test_client ${GLIB_LIBRARIES})
target_link_libraries(test_client ${GIO_LIBRARIES})
