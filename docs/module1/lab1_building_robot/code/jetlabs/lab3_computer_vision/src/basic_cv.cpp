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

    cvtColor(src, gray, CV_BGR2GRAY);

    blur( gray, dst, Size(3,3) );

    Canny(dst, edges, 50, 200, 3);

    cvtColor(edges, cdst, CV_GRAY2BGR);

    HoughLinesP(edges, lines, 1, CV_PI/180, 80, 30, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        line( cdst, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
    }

    sensor_msgs::ImagePtr msg;
    msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cdst).toImageMsg();

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
