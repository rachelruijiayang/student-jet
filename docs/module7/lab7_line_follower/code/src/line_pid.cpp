#include <math.h>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float32.h"
#include "lab7_line_follower/PidConfig.h"

geometry_msgs::Twist vel_msg;
std_msgs::Float32 error_msg;

ros::Publisher vel_pub;
ros::Subscriber line_error_sub;

float integral_error, derivative_error, cur_error, prev_error = 0;
double Kp, Ki, Kd;
bool first_reconfig = true;

void errorCallback(const std_msgs::Float32& msg)
{
    // Stop if the tape is no longer detected
    if(msg.data > 12344 && msg.data < 12346){
        /*
         * ADD CODE HERE
         */
    }else{
        /*
         * ADD CODE HERE
         */
    }

    vel_pub.publish(vel_msg);
}


void reconfigure_callback(lab7_line_follower::PidConfig &config, uint32_t level)
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

int main(int argc, char **argv)
{
  ros::init(argc, argv, "line_pid");
  ros::NodeHandle nh;

  nh.param<double>("Kp", Kp, 0.0);
  nh.param<double>("Ki", Ki, 0.0);
  nh.param<double>("Kd", Kd, 0.0);

  dynamic_reconfigure::Server<lab7_line_follower::PidConfig> config_server;
  dynamic_reconfigure::Server<lab7_line_follower::PidConfig>::CallbackType f;
  f = boost::bind(&reconfigure_callback, _1, _2);
  config_server.setCallback(f);

  line_error_sub = nh.subscribe("/line_error", 10, errorCallback);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

  ros::spin();
}
