cmake_minimum_required(VERSION 2.8.3)
project(lab2_sense_and_avoid)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge image_transport
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(sense_and_avoid src/sense_and_avoid.cpp)
target_link_libraries(sense_and_avoid ${catkin_LIBRARIES})
