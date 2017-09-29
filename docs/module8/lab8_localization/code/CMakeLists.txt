cmake_minimum_required(VERSION 2.8.3)
project(lab8_localization)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  dynamic_reconfigure
  OpenCV
)

find_package(Boost)

generate_dynamic_reconfigure_options(
  cfg/Pid.cfg
  cfg/Segment.cfg
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge image_transport dynamic_reconfigure
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(loc_line_pid src/line_pid.cpp)
add_dependencies(loc_line_pid dynamic_reconfigure ${PROJECT_NAME}_gencfg)
target_link_libraries(loc_line_pid ${catkin_LIBRARIES})

add_executable(loc_line_detector src/line_detector.cpp)
add_dependencies(loc_line_detector dynamic_reconfigure ${PROJECT_NAME}_gencfg)
target_link_libraries(loc_line_detector ${catkin_LIBRARIES})

add_executable(localization src/localization.cpp)
target_link_libraries(localization ${catkin_LIBRARIES})
