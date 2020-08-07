#include "actionlib_basic_server_test_ros.h"

using namespace std;
using namespace ros;

ActionLibBasicRos::ActionLibBasicRos(std::string actionName)
  : as_(nh_, actionName, boost::bind(&ActionLibBasicRos::CbExcute, this, _1), false)
{
  strAction_ = actionName;
  as_.start();
}

ActionLibBasicRos::~ActionLibBasicRos()
{
}

void ActionLibBasicRos::MainLoop()
{
  ROS_INFO_DELAYED_THROTTLE(1, "actionlib_basic_server:test..");
}

void ActionLibBasicRos::CbExcute(const custom_msg_srv_param_ros::FibonacciGoalConstPtr& goal)
{
  // helper variables
  ros::Rate r(1);
  bool success = true;

  // push_back the seeds for the fibonacci sequence
  feedback_.sequence.clear();
  feedback_.sequence.push_back(0);
  feedback_.sequence.push_back(1);

  // publish info to the console for the user
  ROS_INFO("%s: Executing, creating fibonacci sequence of order %i with seeds %i, %i", strAction_.c_str(), goal->order,
           feedback_.sequence[0], feedback_.sequence[1]);

  // start executing the action
  for (int i = 1; i <= goal->order; i++)
  {
    // check that preempt has not been requested by the client
    if (as_.isPreemptRequested() || !ros::ok())
    {
      ROS_INFO("%s: Preempted", strAction_.c_str());
      // set the action state to preempted
      as_.setPreempted();
      success = false;
      break;
    }
    feedback_.sequence.push_back(feedback_.sequence[i] + feedback_.sequence[i - 1]);
    // publish the feedback
    as_.publishFeedback(feedback_);
    // this sleep is not necessary, the sequence is computed at 1 Hz for demonstration purposes
    r.sleep();
  }

  if (success)
  {
    result_.sequence = feedback_.sequence;
    ROS_INFO("%s: Succeeded", strAction_.c_str());

    // set the action state to succeeded
    as_.setSucceeded(result_);
  }
}