cmake_minimum_required(VERSION 2.8.3)
project(lab8_line_follower)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  cfg/Pid.cfg
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge image_transport dynamic_reconfigure
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake
)

add_executable(line_pid src/line_pid.cpp)
add_dependencies(line_pid dynamic_reconfigure ${PROJECT_NAME}_gencfg)
target_link_libraries(line_pid ${catkin_LIBRARIES})

add_executable(line_detector src/line_detector.cpp)
target_link_libraries(line_detector ${catkin_LIBRARIES})

