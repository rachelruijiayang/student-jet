#include "Localization.h"

void Localization::loop() {
    bool stopped = false;
    go_follow_pub.publish(std_msgs::Empty());
    ros::Rate r(10.0);
    while(nh.ok()){
      ros::spinOnce();

      stopped = analyzeState();
      if (!stopped) {
        moveUpdate();
        sensorUpdate();
        resample();
      }
      else {
        stop_follow_pub.publish(std_msgs::Empty());
      }

      r.sleep();
    }
}

void Localization::moveUpdate() {
  /*
   * INSERT CODE HERE
   */
}

void Localization::sensorUpdate() {
  /*
   * INSERT CODE HERE
   */
}

void Localization::resample() {
  /*
   * INSERT CODE HERE
   */
}

bool Localization::analyzeState() {
  tuple<double, double> stats = getCircularStats(particles, MAP_SIZE);
  double mean = get<0>(stats);
  double stddev = get<1>(stats);

  pose_msg.pose.position.x = mean;
  pose_msg.covariance[0] = stddev;
  pose_pub.publish(pose_msg);

  return stddev < stoppingThreshold && mean < 0.5;
}


int main(int argc, char * argv[]) {
  ros::init(argc, argv, "localization");

  Localization localization;
}
