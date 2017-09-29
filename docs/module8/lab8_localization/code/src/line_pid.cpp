#include <math.h>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Empty.h"
#include "lab8_localization/PidConfig.h"

geometry_msgs::Twist vel_msg;
std_msgs::Float32 error_msg;

ros::Publisher vel_pub;
ros::Subscriber line_error_sub, go_follow_sub, stop_follow_sub;

float integral_error, derivative_error, cur_error, prev_error = 0;
double Kp, Ki, Kd;
bool first_reconfig = true;
bool following = false;

void errorCallback(const std_msgs::Float32& msg)
{
    if (following) {
      cur_error = msg.data;

      integral_error += cur_error;
      derivative_error = cur_error - prev_error;
      vel_msg.angular.z = Kp * cur_error + Kd * derivative_error;
      vel_msg.linear.x = 0.7;
      prev_error = cur_error;

      vel_pub.publish(vel_msg);
    }
}


void reconfigure_callback(lab8_localization::PidConfig &config, uint32_t level)
{
  if (first_reconfig)
  {
    first_reconfig = false;
    return;
  }

  Kp = config.Kp * config.Kp_scale;
  Ki = config.Ki * config.Ki_scale;
  Kd = config.Kd * config.Kd_scale;
}

void goCallback(const std_msgs::Empty& msg) {
  following = true;
}

void stopCallback(const std_msgs::Empty& msg) {
  following = false;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "line_pid");
  ros::NodeHandle nh;

  nh.param<double>("Kp", Kp, -0.01);
  nh.param<double>("Ki", Ki, 0.0);
  nh.param<double>("Kd", Kd, -0.03);

  dynamic_reconfigure::Server<lab8_localization::PidConfig> config_server;
  dynamic_reconfigure::Server<lab8_localization::PidConfig>::CallbackType f;
  f = boost::bind(&reconfigure_callback, _1, _2);
  config_server.setCallback(f);

  line_error_sub = nh.subscribe("/line_error", 10, errorCallback);
  go_follow_sub = nh.subscribe("/go_follow", 10, goCallback);
  stop_follow_sub = nh.subscribe("/stop_follow", 10, stopCallback);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  ros::spin();
}
