#include "actionlib_advanced_server_test_ros.h"

using namespace std;
using namespace ros;

ActionLibAdvancedRos::ActionLibAdvancedRos(std::string actionName) : as_(nh_, actionName, false), strAction_(actionName)
{
  // register the goal and feeback callbacks
  as_.registerGoalCallback(boost::bind(&ActionLibAdvancedRos::goalCB, this));
  as_.registerPreemptCallback(boost::bind(&ActionLibAdvancedRos::preemptCB, this));

  // subscribe to the data topic of interest
  sub_ = nh_.subscribe("/random_number", 1, &ActionLibAdvancedRos::analysisCB, this);
  as_.start();
}

ActionLibAdvancedRos::~ActionLibAdvancedRos()
{
}

void ActionLibAdvancedRos::MainLoop()
{
  ROS_INFO_DELAYED_THROTTLE(1, "actionlib_advanced_server:test..");
}

void ActionLibAdvancedRos::goalCB()
{
}

void ActionLibAdvancedRos::preemptCB()
{
}

void ActionLibAdvancedRos::analysisCB(const std_msgs::Float32::ConstPtr& msg)
{
}