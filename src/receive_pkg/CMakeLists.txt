cmake_minimum_required(VERSION 3.10)
project(receive_pkg)

## Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################
## Find dependencies ##
#######################

find_package(OpenCV 4 REQUIRED)
find_package(catkin REQUIRED COMPONENTS
        roscpp
        cv_bridge
        sensor_msgs
        std_msgs
        )

###########
## Build ##
###########

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

add_library(
        ${PROJECT_NAME} STATIC
        src/BaseReceiver.cpp
        src/ImgReceiver.cpp
        src/Int32Receiver.cpp
)


target_link_libraries(${PROJECT_NAME}
        ${catkin_LIBRARIRES}
        )