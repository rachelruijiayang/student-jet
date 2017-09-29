#include <image_transport/image_transport.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/Twist.h"
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <ros/ros.h>
#include <ros/package.h>
#include <lab4_autonomous_driving/classifier.h>
#include <std_msgs/String.h>

using std::string;

geometry_msgs::Twist vel_msg;
ros::Publisher vel_pub;

std_msgs::String dir_msg;
ros::Publisher dir_pub;

Classifier *classifier;

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
  try
  {
    cv::Mat src = cv_bridge::toCvShare(msg, "bgr8")->image;

    cv::Mat icon;
    resize(src, icon, cv::Size(80,60), 0, 0, CV_INTER_AREA );

    Prediction pred = classifier->Classify(src, 1)[0];

    std::cout << std::fixed << std::setprecision(4) << pred.second << " - \""
              << pred.first << "\"" << std::endl;

    dir_msg.data = pred.first;
    dir_pub.publish(dir_msg);
    /*
    if (pred.first == "FORWARD") {
      vel_msg.linear.x = 0.7;
      vel_msg.angular.z = 0.0;
    }
    else if (pred.first == "LEFT") {
      vel_msg.linear.x = 0.2;
      vel_msg.angular.z = -0.5;
    }
    else if (pred.first == "RIGHT") {
      vel_msg.linear.x = 0.2;
      vel_msg.angular.z = 0.5;
    }
    vel_pub.publish(vel_msg);
    */

  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "drive_inference");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  //subscribe to the raw usb camera image
  image_transport::Subscriber raw_image_sub = it.subscribe("/usb_cam/image_raw", 10, imageCallback);

  string base_path = ros::package::getPath("lab4_autonomous_driving");

  string model_file   = base_path + "/neuralnetwork/deploy.prototxt";
  string trained_file = base_path + "/neuralnetwork/models/train_iter_157.caffemodel";
  string mean_file    = base_path + "/resources/data/mean_image.binaryproto";
  string label_file   = base_path + "/neuralnetwork/labels.txt";
  classifier = new Classifier(model_file, trained_file, mean_file, label_file);

  dir_pub = nh.advertise<std_msgs::String>("/lab4_autonomous_driving/direction", 1000);
  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  for(int i = 0; i < 30; i++) {
    string file = base_path + "/resources/img/" + std::to_string(i) + ".jpg";

    std::cout << "---------- Prediction for "
              << file << " ----------" << std::endl;

    cv::Mat img = cv::imread(file, -1);
    CHECK(!img.empty()) << "Unable to decode image " << file;

    cv::Mat icon;
    resize(img, icon, cv::Size(80,60), 0, 0, CV_INTER_AREA );

    Prediction pred = classifier->Classify(icon, 1)[0];

    std::cout << std::fixed << std::setprecision(4) << pred.second << " - \""
              << pred.first << "\"" << std::endl;
  }
  ros::spin();
}
