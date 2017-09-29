#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

cv::Mat src, src_gray;
cv::Mat dst, detected_edges;

image_transport::Publisher pub;
image_transport::Subscriber sub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    src = cv_bridge::toCvShare(msg, "bgr8")->image;

    cv::cvtColor(src , src_gray, CV_BGR2GRAY);

    cv::blur(src_gray, detected_edges, cv::Size(3,3));

    cv::Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

    //Use edges as a mask
    dst = cv::Scalar::all(0);
    src.copyTo(dst, detected_edges);
    
    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", dst).toImageMsg();
    
    pub.publish(msg);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "edge_detection");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);
  
  //advertise the topic with our processed image
  pub = it.advertise("/user/image1", 1);

  //subscribe to the raw usb camear image
  sub = it.subscribe("/cv_camera/image_raw", 1, imageCallback);
  
  ros::spin();
}
