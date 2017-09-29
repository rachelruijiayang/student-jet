#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/Int16.h"

#define LINEAR_SPEED 0.7
#define ANGULAR_SPEED 0.5
#define TURN_DURATION 500
#define OBJECT_DIST_NEAR 30
#define OBJECT_DIST_SAFE 60

enum STATE { FORWARD, REVERSE, TURN };

class SenseAndAvoid
{
  public:
    SenseAndAvoid();

  private:
    void leftEncoderCallback(const std_msgs::Int16::ConstPtr& msg);
    void rightEncoderCallback(const std_msgs::Int16::ConstPtr& msg);
    void sonarCallback(const std_msgs::Int16::ConstPtr& msg);

    ros::NodeHandle nh;

    ros::Publisher vel_pub;

    ros::Subscriber left_encoder_sub;
    ros::Subscriber right_encoder_sub;
    ros::Subscriber sonar_sub;

    geometry_msgs::Twist vel_msg;

    int left_count, right_count;

    STATE state;
};

SenseAndAvoid::SenseAndAvoid()
{
  left_encoder_sub = nh.subscribe<std_msgs::Int16>("/arduino/encoder_left_value", 10, &SenseAndAvoid::leftEncoderCallback, this);
  right_encoder_sub = nh.subscribe<std_msgs::Int16>("/arduino/encoder_right_value", 10, &SenseAndAvoid::rightEncoderCallback, this);
  sonar_sub = nh.subscribe<std_msgs::Int16>("/arduino/sonar_1", 10, &SenseAndAvoid::sonarCallback, this);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  state = FORWARD;
  left_count = 0;
  right_count = 0;
}


void SenseAndAvoid::leftEncoderCallback(const std_msgs::Int16::ConstPtr& msg)
{
  left_count += msg->data;
}

void SenseAndAvoid::rightEncoderCallback(const std_msgs::Int16::ConstPtr& msg)
{
  right_count += msg->data;
}

void SenseAndAvoid::sonarCallback(const std_msgs::Int16::ConstPtr& msg)
{
  if(state == FORWARD && msg->data < OBJECT_DIST_NEAR && msg->data > 0) {
    ROS_INFO("REVERSE");
    state = REVERSE;
    vel_msg.linear.x = -LINEAR_SPEED;
    vel_msg.angular.z = 0;
    vel_pub.publish(vel_msg);
  }
  else if (state == FORWARD) {
    vel_msg.linear.x = LINEAR_SPEED;
    vel_msg.angular.z = 0;
    vel_pub.publish(vel_msg);
  }
  else if(state == REVERSE && msg->data > OBJECT_DIST_SAFE) {
    ROS_INFO("TURN");
    state = TURN;
    vel_msg.linear.x = 0;
    vel_msg.angular.z = ANGULAR_SPEED;
    left_count = 0;
    right_count = 0;
    vel_pub.publish(vel_msg);
  }
  else if (state == TURN && left_count > TURN_DURATION) {
    state = FORWARD;
    ROS_INFO("FORWARD");
    vel_msg.linear.x = LINEAR_SPEED;
    vel_msg.angular.z = 0;
    left_count = 0;
    right_count = 0;
    vel_pub.publish(vel_msg);
  }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "sense_and_avoid");

  SenseAndAvoid sense_and_avoid;

  ros::spin();
}
