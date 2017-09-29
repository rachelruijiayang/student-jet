#include <math.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/Twist.h"
#include <ros/package.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <lab4_autonomous_driving/classifier.h>

using namespace cv;
using namespace std;
using namespace geometry_msgs;

string base_path, vid_path, data_path;

Mat src;
VideoWriter* vidFile;

image_transport::Subscriber raw_image_sub;
ros::Subscriber twist_sub;

ofstream dataFile;

double lin_x, ang_z;

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
  try
  {
    ROS_INFO("%f\n", lin_x);
    src = cv_bridge::toCvShare(msg, "bgr8")->image;

    if(lin_x > 0.0) {
      dataFile << FORWARD_DIR << endl;
      *vidFile << src;
    }
    else if (ang_z > 0.0) {
      dataFile << RIGHT_DIR << endl;
      *vidFile << src;
    }
    else if (ang_z < 0.0) {
      dataFile << LEFT_DIR << endl;
      *vidFile << src;
    }
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void twistCallback(const Twist::ConstPtr& msg) {
  lin_x = msg->linear.x;
  ang_z = msg->angular.z;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "drive_train");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  //subscribe to the raw usb camera image
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 10, imageCallback);

  //subscribe to the velocity vector
  twist_sub = nh.subscribe("/cmd_vel", 10, twistCallback);

  base_path = ros::package::getPath("lab4_autonomous_driving") + "/resources/raw/" + to_string((int)ros::Time::now().toSec());
  vid_path = base_path + ".avi";
  data_path = base_path + ".csv";

  vidFile =  new VideoWriter();
  vidFile->open(vid_path, CV_FOURCC('M','J','P','G'), 30, cv::Size(320,240));

  dataFile.open(data_path.c_str());

  ros::spin();
}
