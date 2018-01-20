cmake_minimum_required(VERSION 3.5)
project(AVClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Multimedia)