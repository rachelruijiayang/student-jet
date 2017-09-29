#include <math.h>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>

using namespace cv;
using namespace std;

cv::Mat src, gray, edges, dst, cdst;
vector<Vec4i> lines;

image_transport::Publisher user_image_pub;
image_transport::Subscriber raw_image_sub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {

    src = cv_bridge::toCvShare(msg, "bgr8")->image;

   /*
     * INSERT CODE HERE
    */

    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", src).toImageMsg();

    user_image_pub.publish(msg);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "basic_cv");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);

  //advertise the topic with our processed image
  user_image_pub = it.advertise("/user/image1", 1);

  //subscribe to the raw usb camera image
  raw_image_sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);

  ros::spin();
}
