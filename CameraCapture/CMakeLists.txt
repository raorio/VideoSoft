cmake_minimum_required(VERSION 2.8)

project(CameraCapture)

message("project name ${PROJECT_NAME}")
message("env OPENCV_PATH $ENV{OPENCV_PATH}")

include_directories(
    "$ENV{OPENCV_PATH}/include"
    "${PROJECT_SOURCE_DIR}"
)   

link_directories($ENV{OPENCV_PATH}/lib) 

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/CameraCapture.cpp)

target_link_libraries("${PROJECT_NAME}" opencv_core220 opencv_highgui220)

