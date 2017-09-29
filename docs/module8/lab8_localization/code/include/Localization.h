#include <math.h>
#include <vector>
#include <utility>
#include <ros/ros.h>
#include <std_msgs/UInt64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/PoseWithCovariance.h>

#define MAP_SIZE 8

using namespace std;

class Localization
{
public:
  Localization();

private:
  void loop();
  void moveUpdate();
  void sensorUpdate();
  void resample();
  void encoderCallback(const std_msgs::UInt64::ConstPtr& msg);
  void sonarCallback(const std_msgs::Int16::ConstPtr& msg);
  bool analyzeState();

  ros::Publisher pose_pub;
  ros::Publisher go_follow_pub;
  ros::Publisher stop_follow_pub;

  ros::Subscriber encoder_sub;
  ros::Subscriber sonar_sub;

  geometry_msgs::PoseWithCovariance pose_msg;
  vector<double> particles;
  vector<double> weights;

  unsigned long long prevEncoderVal;
  unsigned long long encoderVal;
  unsigned short sonarVal;

  double courseLength;
  bool obstacle_map[MAP_SIZE];
  double hitWeightRatio;
  double stoppingThreshold;
  double numParticles;

  default_random_engine generator;
  normal_distribution<double> move_error_distribution;

  ros::NodeHandle nh;
};

Localization::Localization() {
  double moveStdDev;

  //Setup the map
  XmlRpc::XmlRpcValue v;
  nh.param("obstacle_map", v, v);
  if (v.size() != MAP_SIZE) {
    throw std::invalid_argument("Obstacle map must be size 8");
  }
  for(int i = 0; i < MAP_SIZE; i++)
  {
    if (v[i] == "1") {
      obstacle_map[i] = true;
    }
  }

  //Initialize Pose publisher and start/stop line follow publishers
  pose_pub = nh.advertise<geometry_msgs::PoseWithCovariance>("/localized_pose", 10);
  go_follow_pub = nh.advertise<std_msgs::Empty>("/go_follow", 10);
  stop_follow_pub = nh.advertise<std_msgs::Empty>("/stop_follow", 10);

  //Process parameters
  nh.param<double>("~course_length", courseLength, 100.0);
  nh.param<double>("~move_std_dev", moveStdDev, 0.01);
  nh.param<double>("~hit_weight_ratio", hitWeightRatio, 100.0);
  nh.param<double>("~stop_threshold", stoppingThreshold, 0.5);
  nh.param<double>("~num_particles", numParticles, 1000);

  //Configure movement error distribution with parameter as standard deviation
  move_error_distribution = normal_distribution<double>(0.0, moveStdDev);

  //Initialize the particles
  for (int i = 0; i < numParticles; i++) {
    particles.push_back(static_cast <double> (rand()) / (static_cast <float> (RAND_MAX / MAP_SIZE)));
  }

  //Subscribe to encoder and sonar
  sonar_sub = nh.subscribe<std_msgs::UInt64>("/arduino/sonar_3", 10, Localization::sonarCallback, this);
  encoder_sub = nh.subscribe<std_msgs::Int16>("/arduino/encoder_left_value", 10, Localization::encoderCallback, this);

  loop();
}

void Localization::encoderCallback(const std_msgs::UInt64::ConstPtr& msg) {
  encoderVal = msg->data;
}

void Localization::sonarCallback(const std_msgs::Int16::ConstPtr& msg) {
  sonarVal = msg->data;
}

/*
 * Returns the mean and stddev of points given a courseLength
 */
tuple<double, double> getCircularStats(vector<double> points, int courseLength) {
  double sinsum = 0;
  double cossum = 0;
  for (int i = 0; i < points.size(); i++) {
    sinsum += sin(points[i] * M_PI / courseLength * 2.0);
    cossum += cos(points[i] * M_PI / courseLength * 2.0);
  }
  double mean = (atan2(sinsum, cossum) / M_PI * courseLength / 2.0);
  if (mean < 0) {
    mean = 8.0 + mean;
  }
  double sq_errors = 0;
  for (int i = 0; i < points.size(); i++) {
    sq_errors += min(pow(courseLength - points[i] - mean, 2), pow(points[i] - mean, 2));
  }
  double stddev = sqrt(sq_errors) / points.size();
  return make_tuple(mean, stddev);
}
