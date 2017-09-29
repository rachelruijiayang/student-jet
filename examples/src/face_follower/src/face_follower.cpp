#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <ros/package.h>
#include <iostream>
#include <stdio.h>
#include "geometry_msgs/Twist.h"

using namespace std;
using namespace cv;

CascadeClassifier face_cascade;

geometry_msgs::Twist vel_msg;

std::vector<Rect> faces;

cv::Mat frame, frame_gray;
cv::Mat dst, detected_edges;

image_transport::Publisher pub;
image_transport::Subscriber sub;

ros::Publisher vel_pub;

int framesSinceFace;

/**
 * Detects faces and draws an ellipse around them
 */
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    frame = cv_bridge::toCvShare(msg, "bgr8")->image;


    // Convert to gray scale
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

    // Equalize histogram
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3,
				0|CASCADE_SCALE_IMAGE, Size(30, 30));

    framesSinceFace++;

    // Iterate over all of the faces
    for( size_t i = 0; i < faces.size(); i++ ) {
      framesSinceFace = 0;
      // Find center of faces
      Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);

      // Draw ellipse around face
      ellipse(frame, center, Size(faces[i].width/2, faces[i].height/2),
	    0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

      if (i == 0) {
         vel_msg.angular.z = -2.5 * (center.x - (static_cast<double>(frame.cols) / 2)) / static_cast<double>(frame.cols);
         vel_pub.publish(vel_msg);
      }
    }

    //Stop the robot from turning if no face is 5 frames    
    if (framesSinceFace > 5) {
      vel_msg.angular.z = 0.0;
      vel_pub.publish(vel_msg);
    }

    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
    
    pub.publish(msg);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "face_follower");
  ros::NodeHandle nh;

  framesSinceFace = 0;

  string xmlpath = ros::package::getPath("face_follower") + "/resources/haarcascade_frontalface_alt.xml";
  face_cascade.load(xmlpath);

  image_transport::ImageTransport it(nh);
  
  pub = it.advertise("/user/image1", 1);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  sub = it.subscribe("/cv_camera/image_raw", 1, imageCallback);
  
  ros::spin();
}
