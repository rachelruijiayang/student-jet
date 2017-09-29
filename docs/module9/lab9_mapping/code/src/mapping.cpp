#include <math.h>
#include <vector>
#include <utility>
#include <ros/ros.h>
#include <std_msgs/UInt64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Point32.h>

#define CENTIMETERS_PER_METER 100.0

using namespace std;

class Mapping
{
public:
  Mapping();

private:
  ros::NodeHandle nh;
};

Mapping::Mapping() {
}


int main(int argc, char * argv[]) {
  ros::init(argc, argv, "mapping");

  Mapping Mapping;
}
