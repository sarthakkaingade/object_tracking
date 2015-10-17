cmake_minimum_required(VERSION 2.8.3)
project(object_tracking)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg sensor_msgs cv_bridge image_transport)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(object_tracking src/object_tracking.cpp)
target_link_libraries(object_tracking ${catkin_LIBRARIES})
add_dependencies(object_tracking object_tracking_generate_messages_cpp)
