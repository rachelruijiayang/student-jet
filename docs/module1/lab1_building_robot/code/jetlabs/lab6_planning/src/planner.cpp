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
   set<Point> closedSet;
   set<Point> openSet;
   Point current, neighbor;
   map<Point,Point> cameFrom;
   map<Point, double> gScore;
   map<Point, double> fScore;
   geometry_msgs::PoseStamped curPose;

   Point first, last;
   this->costmap.worldToMap(start.pose.position.x, start.pose.position.y, first.x, first.y);
   this->costmap.worldToMap(goal.pose.position.x, goal.pose.position.y, last.x, last.y);

   openSet.insert(first);

   gScore[first] = 0.0;
   fScore[first] = dist(first, last);

   while(!openSet.empty()) {
     current = *openSet.begin();
     for(auto it = openSet.begin(); it != openSet.end(); it++) {
       if (fScore[*it] < fScore[current])
          current = *it;
     }

     if(current == last) {
        break;
     }
      closedSet.insert(current);
      openSet.erase(current);

      vector<Point> neighbors = getNeighbors(current);
      for(auto it = neighbors.begin(); it != neighbors.end(); it++ ) {
        if (it->x > this->costmap.getSizeInCellsX() || it->x < 0)
          continue;
        if (it->y > this->costmap.getSizeInCellsY() || it->y < 0)
          continue;
        if (closedSet.count(*it) > 0) {
          continue;
        }
        if (this->costmap.getCost(it->x, it->y) > 0) {
          continue;
        }
        double tentative_gScore = gScore[current] + 1;
        if (openSet.count(*it) == 0) {
          openSet.insert(*it);
        }
        else if (tentative_gScore >= gScore[*it]) {
          continue;
        }
        cameFrom[*it] = current;
        gScore[*it] = tentative_gScore;
        fScore[*it] = gScore[*it] + dist(*it, last);
      }
   }

   this->costmap.worldToMap(goal.pose.position.x, goal.pose.position.y, current.x, current.y);
   plan.insert(plan.begin(), goal);
   while (cameFrom.count(current) > 0) {
     current = cameFrom[current];
     this->costmap.mapToWorld(current.x, current.y, curPose.pose.position.x, curPose.pose.position.y);
     plan.insert(plan.begin(), curPose);
   }
  return true;
 }
}
