cmake_minimum_required(VERSION 3.10)
project(publish_pkg)

## Use C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#######################
## Find dependencies ##
#######################


find_package(catkin REQUIRED COMPONENTS
        roscpp
        cv_bridge
        sensor_msgs
        std_msgs
        )

find_package(OpenCV 4 REQUIRED)
###########
## Build ##
###########
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_NAME}
)


include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

add_library(
        ${PROJECT_NAME} STATIC
        src/BasePublisher.cpp
        src/ImgPublisher.cpp
        src/Int32Publisher.cpp
)

target_link_libraries(
        ${PROJECT_NAME}
        ${catkin_LIBRARIRES}
        ${OpenCV_LIBS}
        )