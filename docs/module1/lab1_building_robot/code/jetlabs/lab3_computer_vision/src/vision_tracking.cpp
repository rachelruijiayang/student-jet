#include <math.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/Twist.h"
#include <dynamic_reconfigure/server.h>
#include "lab3_computer_vision/HueConfig.h"

cv::Moments moments;
cv::Mat src, hsv, mask;
cv::Mat dst, cdst;
cv::Point center_of_mass;

image_transport::Publisher user_image_pub;
image_transport::Subscriber raw_image_sub;

ros::Publisher vel_pub;

geometry_msgs::Twist vel_msg;

double line_center = 0;
int intersections = 0;

int hue_lower, hue_upper, sat_lower, sat_upper, value_lower, value_upper;
bool first_reconfig = true;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    src = cv_bridge::toCvShare(msg, "bgr8")->image;

    //Convert the image to HSV
    cv::cvtColor(src, hsv, CV_BGR2HSV);

    //Define the range of blue pixels
    cv::Scalar lower_thresh(hue_lower, sat_lower, value_lower);
    cv::Scalar upper_thresh(hue_upper, sat_upper, value_upper);

    //Create a mask with only blue pixels
    cv::inRange(hsv, lower_thresh, upper_thresh, mask);

    //Calculate moments of mask
    moments = cv::moments(mask, true);

    //Calculate center of mass using moments
    center_of_mass.x = moments.m10 / moments.m00;
    center_of_mass.y = moments.m01 / moments.m00;

    //Conert the image back to BGR
    cv::cvtColor(mask, dst, CV_GRAY2BGR);

    //Plot the center of mass
    cv::circle(dst, center_of_mass, 5, cv::Scalar(0,0,255), -1);

    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", dst).toImageMsg();

    user_image_pub.publish(msg);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void reconfigure_callback(lab3_computer_vision::HueConfig &config, uint32_t level)
{
  if (first_reconfig)
  {
    first_reconfig = false;
    return;
  }

  hue_lower = config.hue_lower;
  hue_upper = config.hue_upper;
  sat_lower = config.sat_lower;
  sat_upper = config.sat_upper;
  value_lower = config.value_lower;
  value_upper = config.value_upper;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "vision_tracking");
  ros::NodeHandle nh;

  ros::NodeHandle nh_("~");
  nh_.param<int>("hue_lower", hue_lower, 80);
  nh_.param<int>("hue_upper", hue_upper, 150);
  nh_.param<int>("sat_lower", sat_lower, 20);
  nh_.param<int>("sat_upper", sat_upper, 255);
  nh_.param<int>("value_lower", value_lower, 20);
  nh_.param<int>("value_upper", value_upper, 255);

  image_transport::ImageTransport it(nh);

  dynamic_reconfigure::Server<lab3_computer_vision::HueConfig> config_server;
  dynamic_reconfigure::Server<lab3_computer_vision::HueConfig>::CallbackType f;
  f = boost::bind(&reconfigure_callback, _1, _2);
  config_server.setCallback(f);

  //advertise the topic with our processed image
  user_image_pub = it.advertise("/user/image1", 1);

  //subscribe to the raw usb camera image
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);

  ros::spin();
}
