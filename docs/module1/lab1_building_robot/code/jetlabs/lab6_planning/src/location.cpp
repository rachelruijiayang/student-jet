#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_broadcaster");

  ros::NodeHandle node;

  tf::Transform transform;
  static tf::TransformBroadcaster br;
  transform.setOrigin( tf::Vector3(0.0, 0.0, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, 0.0);
  transform.setRotation(q);

  ros::Rate loop_rate(1000);

    int count = 0;
    while (ros::ok())
    {
      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));
      br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_footprint"));

      ros::spinOnce();

      loop_rate.sleep();
      ++count;
    }

  return 0;
};
