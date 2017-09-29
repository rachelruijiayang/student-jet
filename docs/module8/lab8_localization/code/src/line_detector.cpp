#include <math.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/Float32.h"
#include <dynamic_reconfigure/server.h>
#include "lab8_localization/SegmentConfig.h"

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
bool first_reconfig = true;

int hue_lower, hue_upper, saturation_lower, saturation_upper, value_lower, value_upper;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {

    src = cv_bridge::toCvShare(msg, "bgr8")->image;

    //Convert the image to HSV
    cv::cvtColor(src, hsv, CV_BGR2HSV);

    cv::Scalar lower_thresh(hue_lower, saturation_lower, value_lower);
    cv::Scalar upper_thresh(hue_upper, saturation_upper, value_upper);

    //Create a mask with only blue pixels
    cv::inRange(hsv, lower_thresh, upper_thresh, mask);

    //Calculate moments of mask
    moments = cv::moments(mask, true);

    //Compute Center of Mass
    center_of_mass.x = moments.m10 / moments.m00;
    center_of_mass.y = moments.m01 / moments.m00;

    //Calculate Noramlized Error
    error_msg.data = center_of_mass.x - src.cols/2;
    line_error_pub.publish(error_msg);

    //Conert the image back to BGR
    cv::cvtColor(mask, dst, CV_GRAY2BGR);

    //Plot the center of mass
    cv::circle(dst, center_of_mass, 5, cv::Scalar(0,0,255), -1);

    // outputting photo captures for analysis on another machine (quicker re-thresholding)
    cv::imwrite("/home/ubuntu/original.png",hsv);
    cv::imwrite("/home/ubuntu/thresh.png",dst);

    sensor_msgs::ImagePtr msg;

    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", dst).toImageMsg();

    user_image_pub.publish(msg);

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}


void reconfigure_callback(lab8_localization::SegmentConfig &config, uint32_t level)
{
  if (first_reconfig)
  {
    first_reconfig = false;
    return;
  }
  hue_lower = config.hue_lower;
  hue_upper = config.hue_upper;
  saturation_lower = config.saturation_lower;
  saturation_upper = config.saturation_upper;
  value_lower = config.value_lower;
  value_upper = config.value_upper;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "line_detector");
  ros::NodeHandle nh;

  dynamic_reconfigure::Server<lab8_localization::SegmentConfig> config_server;
  dynamic_reconfigure::Server<lab8_localization::SegmentConfig>::CallbackType f;
  f = boost::bind(&reconfigure_callback, _1, _2);
  config_server.setCallback(f);

  nh.param<int>("hue_lower", hue_lower, 0);
  nh.param<int>("hue_upper", hue_upper, 180);
  nh.param<int>("saturation_lower", saturation_lower, 0);
  nh.param<int>("saturation_upper", saturation_upper, 255);
  nh.param<int>("value_lower", value_lower, 67);
  nh.param<int>("value_upper", value_upper, 255);

  //configure image transport
  image_transport::ImageTransport it(nh);

  //advertise the topic that outputs line error
  line_error_pub = nh.advertise<std_msgs::Float32>("/line_error", 10);

  //advertise the topic with our processed image
  user_image_pub = it.advertise("/user/image1", 10);

  //subscribe to the raw usb camera image
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 10, imageCallback);

  ros::spin();
}
