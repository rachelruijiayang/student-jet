cmake_minimum_required(VERSION 2.8.3)
project(lab4_autonomous_driving)

set(CMAKE_CXX_FLAGS "-DCPU_ONLY -std=c++0x ${CMAKE_CXX_FLAGS}")

set(CAFFE_LINK_LIBRARAY ~/caffe/build/lib)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
)

find_package(OpenCV REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rospy std_msgs cv_bridge image_transport
)

add_library(${PROJECT_NAME} src/classifier.cpp src/drive_inference.cpp)


include_directories(
  "~/caffe/include"
  "~/caffe/build/src"
  ${catkin_INCLUDE_DIRS}
  include ${catkin_INCLUDE_DIRS}
)

link_directories(${CAFFE_LINK_LIBRARAY})

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  )

install(PROGRAMS scripts/preprocess.py
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

add_executable(drive_train src/drive_train.cpp src/classifier.cpp)
target_link_libraries(drive_train ${catkin_LIBRARIES} caffe glog)

add_executable(drive_inference src/drive_inference.cpp src/classifier.cpp)
target_link_libraries(drive_inference ${catkin_LIBRARIES} caffe glog)
