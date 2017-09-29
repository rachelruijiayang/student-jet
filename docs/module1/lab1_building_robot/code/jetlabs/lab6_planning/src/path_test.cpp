#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <nav_msgs/GetPlan.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  ros::NodeHandle nh;

  ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("/test_plan", 10);
  ros::ServiceClient client = nh.serviceClient<nav_msgs::GetPlan>("move_base/make_plan");

  nav_msgs::GetPlan srv;
  srv.request.goal.pose.position.x =  7.091;
  srv.request.goal.pose.position.y = -7.197;

  if (client.call(srv))
  {
    srv.response.plan.header.frame_id = "base_link";
    while(1) {
      path_pub.publish(srv.response.plan);
      ros::spinOnce();
      ros::Duration(1.0).sleep();
    }
  }
  else
  {
    ROS_ERROR("Failed to call service");
    return 1;
  }

  return 0;
}
