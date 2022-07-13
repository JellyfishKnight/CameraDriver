cmake_minimum_required(VERSION 3.0.2)
project(publish_pkg)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  sensor_msgs
  std_msgs
)

find_package(OpenCV 4 REQUIRED)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ library
 add_library(
         ${PROJECT_NAME} STATIC
         src/BasePublisher.cpp
         src/ImgPublisher.cpp
 )

## Specify libraries to link a library or executable target against
 target_link_libraries(
         ${PROJECT_NAME}
         ${catkin_LIBRARIES}
         ${OpenCV_LIBS}
 )

