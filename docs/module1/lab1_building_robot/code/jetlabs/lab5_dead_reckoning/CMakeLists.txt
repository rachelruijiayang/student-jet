cmake_minimum_required(VERSION 2.8.3)
project(lab5_dead_reckoning)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(dead_reckoning src/dead_reckoning.cpp)
target_link_libraries(dead_reckoning ${catkin_LIBRARIES})
