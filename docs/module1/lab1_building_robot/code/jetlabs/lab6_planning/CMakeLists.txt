cmake_minimum_required(VERSION 2.8.3)
project(lab6_planning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( PCL REQUIRED )
include_directories(  ${catkin_INCLUDE_DIRS}  ${PCL_INCLUDE_DIRS} )
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  dynamic_reconfigure
  tf
)

find_package(catkin REQUIRED COMPONENTS tf)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge image_transport
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include ${catkin_INCLUDE_DIRS}
)
add_executable(location src/location.cpp)
target_link_libraries(location ${catkin_LIBRARIES})

add_library(global_planner_lib src/planner.cpp)

add_executable(path_test src/path_test.cpp)
target_link_libraries(path_test ${catkin_LIBRARIES})
