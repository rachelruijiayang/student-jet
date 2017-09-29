#include <set>
#include <pluginlib/class_list_macros.h>
#include <lab6_planning/planner.h>
#include <math.h>

//register this planner as a BaseGlobalPlanner plugin
PLUGINLIB_EXPORT_CLASS(global_planner::GlobalPlanner, nav_core::BaseGlobalPlanner)


using namespace std;


struct Point {
        unsigned int x;
        unsigned int y;
        bool const operator==(const Point &o) {
                return x == o.x && y == o.y;
        }

        bool const operator<(const Point &o) const {
                return x < o.x || (x == o.x && y < o.y);
        }
};

double dist(Point p1, Point p2) {
        return sqrt((p1.x - p2.x) ^ 2 + (p1.y - p2.y) ^ 2);
}

vector<Point> getNeighbors(Point pt) {
        vector<Point> neighbors;
        pt.x -= 1;
        neighbors.push_back(pt);
        pt.x += 2;
        neighbors.push_back(pt);
        pt.x -= 1;
        pt.y += 1;
        neighbors.push_back(pt);
        pt.y -= 2;
        neighbors.push_back(pt);
        return neighbors;
}

//Default Constructor
namespace global_planner {

GlobalPlanner::GlobalPlanner (){

}

GlobalPlanner::GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
        initialize(name, costmap_ros);
}


void GlobalPlanner::initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros){
        this->costmap = *costmap_ros->getCostmap();
}

bool GlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start, const geometry_msgs::PoseStamped& goal,  std::vector<geometry_msgs::PoseStamped>& plan ){
        geometry_msgs::PoseStamped current;


        // Sample Path Creation
        for (int i = 0; i < 7; i++) {
          current.pose.position.x = i;
          current.pose.position.y = i;
          plan.push_back(current);
        }

        /*
         * INSERT PLANNING ALGORITHM HERE
         */

        return true;
}
}
