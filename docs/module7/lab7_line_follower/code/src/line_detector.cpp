#include <math.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/Float32.h"

cv::Moments moments;
cv::Mat src, hsv, mask;
cv::Mat dst, cdst;
cv::Point center_of_mass;

image_transport::Publisher user_image_pub;
image_transport::Subscriber raw_image_sub;

ros::Publisher line_error_pub;

std_msgs::Float32 error_msg;

double line_center = 0;
int intersections = 0;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    /*
     * ADD CODE HERE
     */
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "line_detector");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  //advertise the topic that outputs line error
  line_error_pub = nh.advertise<std_msgs::Float32>("/line_error", 10);

  //advertise the topic with our processed image
  user_image_pub = it.advertise("/user/image1", 10);

  //subscribe to the raw usb camera image
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 10, imageCallback);

  ros::spin();
}
