#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <math.h>


cv::Mat src, src_gray;
cv::Mat dst, detected_edges;
cv::vector<cv::Vec3f> circles;

image_transport::Publisher pub;
image_transport::Subscriber sub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    src = cv_bridge::toCvShare(msg, "bgr8")->image;

    cv::cvtColor(src , src_gray, CV_BGR2GRAY);

    cv::GaussianBlur(src_gray, detected_edges, cv::Size(3,3), 2, 2);

    cv::HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0);

    for (int i = 0; i < circles.size(); i++)
    {
       cv::Point center(round(circles[i][0]), round(circles[i][1]));
       int radius =  round(circles[i][2]);
       cv::circle(src, center, 3, cv::Scalar(0,255,0), -1, 8, 0);
       cv::circle(src, center, radius, cv::Scalar(0,0,255), 3, 8, 0);
    }

    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", src).toImageMsg();
    
    pub.publish(msg);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "circle_counting");
  ros::NodeHandle nh;

  image_transport::ImageTransport it(nh);
  
  //advertise the topic with our processed image
  pub = it.advertise("/user/image1", 1);

  //subscribe to the raw usb camear image
  sub = it.subscribe("/cv_camera/image_raw", 1, imageCallback);
  
  ros::spin();
}
