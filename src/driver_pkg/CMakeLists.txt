cmake_minimum_required(VERSION 3.0.2)
project(driver_pkg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        publish_pkg
        cv_bridge
        sensor_msgs
)

find_package(OpenCV 4 REQUIRED)


include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

set(TargetClass src/BaseDriver.cpp src/MindVision.cpp)

# Declare a C++ library
 add_library(${PROJECT_NAME} STATIC
         ${TargetClass}
 )

add_executable(${PROJECT_NAME}_node src/driver_pkg_node)


target_link_libraries(
        ${PROJECT_NAME}_node
        ${catkin_LIBRARIES}
        MVSDK
        ${OpenCV_LIBS}
        ${PROJECT_NAME}
        )
#*********************************
#cmake_minimum_required(VERSION 3.0.2)
#project(recognize_pkg)
#
#find_package(catkin REQUIRED COMPONENTS
#        receive_pkg
#        roscpp
#        )
#
#find_package(OpenCV 4 REQUIRED)
#
#
#include_directories(
#        include
#        ${catkin_INCLUDE_DIRS}
#        ${OpenCV_INCLUDE_DIRS}
#)
#
#add_library(${PROJECT_NAME}
#        src/PreProcess.cpp
#        src/Ranger.cpp
#        src/System.cpp
#        src/DataReader.cpp
#        )
#
#add_executable(${PROJECT_NAME}_node src/recognize_pkg_node.cpp)
#
#target_link_libraries(${PROJECT_NAME}_node
#        ${catkin_LIBRARIES}
#        ${OpenCV_LIBS}
#        ${PROJECT_NAME}
#        )
