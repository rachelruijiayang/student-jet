#include <math.h>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/UInt64.h"
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>

/*
 * MODIFY THESE VALUES TO ACHIEVE BETTER ACCURACY
 */
#define WHEEL_RADIUS 0.07
#define WHEEL_SEPARATION 0.36
#define TICKS_PER_REVOLUTION 300

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

    /*
     * DECLARE CLASS FIELDS HERE
     */
};

DeadReckoning::DeadReckoning()
{
  ros::Subscriber left_sub = nh.subscribe<std_msgs::UInt64>("/arduino/encoder_left_value", 10, &DeadReckoning::leftEncoderCallback, this);
  ros::Subscriber right_sub = nh.subscribe<std_msgs::UInt64>("/arduino/encoder_right_value", 10, &DeadReckoning::rightEncoderCallback, this);
  ros::Subscriber goal_sub = nh.subscribe<geometry_msgs::Pose>("/dead_reckoning/goal", 10, &DeadReckoning::goalCallback, this);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  odom_pub = nh.advertise<nav_msgs::Odometry>("/myodom", 50);

  navigating = false;

  /*
   * INSERT VARIABLE INITIALIZATION
   */

  loop();
}

void DeadReckoning::publishOdom()
{

  /*
   * INSERT ODOMETRY CALCULATIONS HERE
   */

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

    /*
     * INSERT MOVE CODE HERE
     */

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
