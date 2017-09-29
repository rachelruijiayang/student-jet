cmake_minimum_required(VERSION 2.8.3)
project(lab3_computer_vision)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  cfg/Hue.cfg
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge image_transport dynamic_reconfigure
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${dynamic_reconfigure_PACKAGE_PATH}/cmake/cfgbuild.cmake
)

add_executable(basic_cv src/basic_cv.cpp)
add_dependencies(basic_cv dynamic_reconfigure ${PROJECT_NAME}_gencfg)
target_link_libraries(basic_cv ${catkin_LIBRARIES})

add_executable(vision_tracking src/vision_tracking.cpp)
target_link_libraries(vision_tracking ${catkin_LIBRARIES})
