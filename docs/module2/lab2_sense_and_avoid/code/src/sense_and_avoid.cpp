#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "std_msgs/UInt64.h"
#include "std_msgs/Int16.h"

#define LINEAR_SPEED 1.4
#define ANGULAR_SPEED 4.0
#define TURN_DURATION 500
#define REVERSE_DURATION 400
#define OBJECT_DIST_NEAR 60
#define OBJECT_DIST_SAFE 120

enum STATE { FORWARD, REVERSE, TURN };

class SenseAndAvoid
{
  public:
    SenseAndAvoid();

  private:
    void leftEncoderCallback(const std_msgs::UInt64::ConstPtr& msg);
    void rightEncoderCallback(const std_msgs::UInt64::ConstPtr& msg);
    void sonarCallback(const std_msgs::Int16::ConstPtr& msg);

    ros::NodeHandle nh;

    ros::Publisher vel_pub;

    ros::Subscriber left_encoder_sub;
    ros::Subscriber right_encoder_sub;
    ros::Subscriber sonar_sub;

    geometry_msgs::Twist vel_msg;

    long left_count, right_count;
    long last_count;
    STATE state;
};

SenseAndAvoid::SenseAndAvoid()
{
  left_encoder_sub = nh.subscribe<std_msgs::UInt64>("/arduino/encoder_left_value", 10, &SenseAndAvoid::leftEncoderCallback, this);
  right_encoder_sub = nh.subscribe<std_msgs::UInt64>("/arduino/encoder_right_value", 10, &SenseAndAvoid::rightEncoderCallback, this);
  sonar_sub = nh.subscribe<std_msgs::Int16>("/arduino/sonar_2", 10, &SenseAndAvoid::sonarCallback, this);

  vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

  state = FORWARD;
  left_count = 0;
  right_count = 0;
}


void SenseAndAvoid::leftEncoderCallback(const std_msgs::UInt64::ConstPtr& msg)
{
  /*
   * ADD YOUR CODE HERE
   */
}

void SenseAndAvoid::rightEncoderCallback(const std_msgs::UInt64::ConstPtr& msg)
{
  /*
   * ADD YOUR CODE HERE
   */
}

void SenseAndAvoid::sonarCallback(const std_msgs::Int16::ConstPtr& msg)
{
  /*
   * ADD YOUR CODE HERE
   */

  //if (going forward and there is a nearby object)
  //else if (going forward)
  //else if (going backwards and objects are far away and have moved more than REVERSE_DURATION)
  //else if (turning and have turned more than TURN_DURATION)

  vel_pub.publish(vel_msg);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "sense_and_avoid");

  SenseAndAvoid sense_and_avoid;

  ros::spin();
}
