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

  strAction_ = actionName;
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
  // reset helper variables
  dataCount_ = 0;
  sum_ = 0;
  sumSq_ = 0;

  // accept the new goal
  goal_ = as_.acceptNewGoal()->samples;
  ROS_INFO("receive new goal:%d", goal_);
}

void ActionLibAdvancedRos::preemptCB()
{
  ROS_INFO("%s: Preempted", strAction_.c_str());

  // set the action state to preempted
  as_.setPreempted();
}

void ActionLibAdvancedRos::analysisCB(const std_msgs::Float32::ConstPtr& msg)
{
  // make sure that the action hasn't been canceled
  if (!as_.isActive())
    return;

  dataCount_++;
  feedback_.sample = dataCount_;
  feedback_.data = msg->data;

  // compute the std_dev and mean of the data
  sum_ += msg->data;
  feedback_.mean = sum_ / dataCount_;
  sumSq_ += pow(msg->data, 2);
  feedback_.std_dev = sqrt(fabs((sumSq_ / dataCount_) - pow(feedback_.mean, 2)));
  as_.publishFeedback(feedback_);

  // meet the condition, it can generate the result
  if (dataCount_ > goal_)
  {
    result_.mean = feedback_.mean;
    result_.std_dev = feedback_.std_dev;

    if (result_.mean < 5.0)
    {
      ROS_INFO("%s: Aborted(mean:%.4f, std_dev:%.4f)", strAction_.c_str(), result_.mean, result_.std_dev);

      // set the action state to aborted
      as_.setAborted(result_);
    }
    else
    {
      ROS_INFO("%s: Succeeded(mean:%.4f, std_dev:%.4f)", strAction_.c_str(), result_.mean, result_.std_dev);

      // set the action state to succeeded
      as_.setSucceeded(result_);
    }
  }
  else
    ROS_INFO("(goal,received):(%d,%d)", goal_, dataCount_);
}