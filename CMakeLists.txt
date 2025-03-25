cmake_minimum_required(VERSION 3.10)

project(data_recorder VERSION 1.0.0)

SET(CMAKE_CXX_STANDARD 17)

#=======================================
# Compile setup (ORIGINAL, CATKIN, COLCON)
#=======================================
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O4 -s -Wall -Wno-sign-compare -Wno-unused -Wno-comment -Wno-deprecated-declarations -g -pthread")


#========================
# Dependencies Setup
#========================
#ROS#
find_package(roscpp 1.12 QUIET)
if(roscpp_FOUND)
  message(=============================================================)
  message("-- ROS Found, Ros Support is turned On!")
  message(=============================================================)
  add_definitions(-DROS_FOUND)
  find_package(catkin REQUIRED COMPONENTS
    roscpp
    rosbag
    # msgs
    std_msgs
    sensor_msgs
    nav_msgs
  )

  find_package(roslib QUIET)

  catkin_package(

  )

  include_directories(${catkin_INCLUDE_DIRS})

else()
  message(=============================================================)
  message("-- ROS Not Found, Ros Support is turned Off!")
  message(=============================================================)
endif()

# include directories
include_directories(
        include
)

# link directories
link_directories(
        include
)

#============================
#  Build Lib, App, Tests
#============================



#############
##  Nodes  ##
#############

add_executable(vins_recorder app/vins_recorder.cc)
target_link_libraries(vins_recorder ${catkin_LIBRARIES})


