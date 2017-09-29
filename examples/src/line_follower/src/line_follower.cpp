#include <math.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/Twist.h"

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

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {

    src = cv_bridge::toCvShare(msg, "bgr8")->image;

    //Convert the image to HSV
    cv::cvtColor(src, hsv, CV_BGR2HSV);

    //Define the range of blue pixels
    cv::Scalar lower_thresh(80,50,50);
    cv::Scalar upper_thresh(150, 255,255);

    //Create a mask with only blue pixels
    cv::inRange(hsv, lower_thresh, upper_thresh, mask);

    //Calculate moments of mask
    moments = cv::moments(mask, true);

    //Calculate center of mass using moments
    center_of_mass.x = moments.m10 / moments.m00;
    center_of_mass.y = moments.m01 / moments.m00;    

    //Compute and publish the robot velocity
    vel_msg.angular.z = (-1.0 * center_of_mass.x / src.cols + 0.5) / 3.0;
    vel_pub.publish(vel_msg);

    ROS_INFO("%f", vel_msg.angular.z);

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

int main(int argc, char **argv)
{
  ros::init(argc, argv, "line_follower");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);
  
  //advertise the topic with our processed image
  user_image_pub = it.advertise("/user/image1", 1);

  //subscribe to the raw usb camera image
  raw_image_sub = it.subscribe("/cv_camera/image_raw", 1, imageCallback);
  
  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  vel_msg.linear.x = .2;

  ros::spin();
}
