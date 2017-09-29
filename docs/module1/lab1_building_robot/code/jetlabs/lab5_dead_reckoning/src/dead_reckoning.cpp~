#include <math.h>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/UInt64.h"
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>

#define WHEEL_RADIUS 0.07
#define WHEEL_SEPARATION 0.36
#define TICKS_PER_REVOLUTION 300
#define EPSILON 0.01

class DeadReckoning
{
  public:
    DeadReckoning();

  private:
    void loop();
    void publishOdom();
    void move();

    void leftEncoderCallback(const std_msgs::UInt64::ConstPtr& msg);
    void rightEncoderCallback(const std_msgs::UInt64::ConstPtr& msg);
    void goalCallback(const geometry_msgs::Pose::ConstPtr& msg);

    ros::NodeHandle nh;

    ros::Publisher vel_pub;
    ros::Publisher odom_pub;

    geometry_msgs::Twist vel_msg;
    geometry_msgs::Pose goal;
    nav_msgs::Odometry odom;

    unsigned long left_count, right_count;
    bool navigating;

    ros::Time cur_time, prev_time;

    double prev_left, prev_right;
    double linear_vel, angular_vel, x_pos, y_pos, direction, angle;
    double time_step;
};

DeadReckoning::DeadReckoning()
{
  ros::Subscriber left_sub = nh.subscribe<std_msgs::UInt64>("/arduino/encoder_left_value", 10, &DeadReckoning::leftEncoderCallback, this);
  ros::Subscriber right_sub = nh.subscribe<std_msgs::UInt64>("/arduino/encoder_right_value", 10, &DeadReckoning::rightEncoderCallback, this);
  ros::Subscriber goal_sub = nh.subscribe<geometry_msgs::Pose>("/dead_reckoning/goal", 10, &DeadReckoning::goalCallback, this);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  odom_pub = nh.advertise<nav_msgs::Odometry>("/myodom", 50);

  navigating = false;

  cur_time = ros::Time::now();
  prev_time = ros::Time::now();

  prev_left = 0;
  prev_right = 0;

  x_pos = 0;
  y_pos = 0;
  angle = 0;

  left_count = 0;
  right_count = 0;

  loop();
}

void DeadReckoning::publishOdom()
{
  double cur_left = (double)left_count / TICKS_PER_REVOLUTION * WHEEL_RADIUS;
  double cur_right = (double)right_count / TICKS_PER_REVOLUTION * WHEEL_RADIUS;

  double diff_left = cur_left - prev_left;
  double diff_right = cur_right - prev_right;

  prev_left = cur_left;
  prev_right = cur_right;

  double linear_vel = (diff_left + diff_right) / 2.0;
  double angular_vel = (diff_right - diff_left) / WHEEL_SEPARATION;

  double direction = angle + angular_vel / 2.0;
  x_pos += linear_vel * cos(direction);
  y_pos += linear_vel * sin(direction);
  angle += angular_vel;

  cur_time = ros::Time::now();
  double time_step = (cur_time - prev_time).toSec();
  prev_time = cur_time;

  odom.header.stamp = cur_time;
  odom.header.frame_id = "odom";
  odom.child_frame_id = "base_link";

  odom.pose.pose.position.x = x_pos;
  odom.pose.pose.position.y = y_pos;
  odom.pose.pose.position.z = 0.0;
  odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(angle);

  odom.twist.twist.linear.x = linear_vel / time_step;
  odom.twist.twist.angular.z = angular_vel / time_step;

  odom_pub.publish(odom);
}

void DeadReckoning::move()
{
  if (navigating) {
    double unit_angle = angle - 2 * M_PI * floor(angle / (2 * M_PI));
    double y_diff = goal.position.y - odom.pose.pose.position.y;
    double x_diff = goal.position.x - odom.pose.pose.position.x;

    if (fabs(x_diff) < 0.2 && fabs(y_diff) < 0.2) {
        navigating = false;
        return;
    }

    if (fabs(x_diff) < 0.01) {
      x_diff = x_diff < 0 ? -0.01 : 0.01;
    }

    double goal_angle = atan2(y_diff, x_diff);

    if (fabs(goal_angle - unit_angle) > 0.1) {
      vel_msg.angular.z = goal_angle - unit_angle > 0 ? 1.0 : - 1.0;
      vel_msg.linear.x = 0.7;
    }
    else {
      vel_msg.angular.z = 0.0;
      vel_msg.linear.x = 0.9;
    }
    vel_pub.publish(vel_msg);
  }
}

void DeadReckoning::loop()
{
  ros::Rate r(10.0);
  while(nh.ok()){
    ros::spinOnce();

    publishOdom();

    move();

    r.sleep();
  }
}

void DeadReckoning::leftEncoderCallback(const std_msgs::UInt64::ConstPtr& msg)
{
  left_count = msg->data;
}

void DeadReckoning::rightEncoderCallback(const std_msgs::UInt64::ConstPtr& msg)
{
  right_count = msg->data;
}

void DeadReckoning::goalCallback(const geometry_msgs::Pose::ConstPtr& msg) {
    if (!navigating) {
      navigating = true;
      goal = *msg;
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dead_reckoning");
  ros::NodeHandle nh;

  DeadReckoning deadReckoning;
}
