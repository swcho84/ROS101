#include "actionlib_advanced_client_test_ros.h"

using namespace std;
using namespace ros;

ActionLibAdvancedClientRos::ActionLibAdvancedClientRos(std::string actionName) : ac_(actionName, true)
{
  // waiting the action server
  ROS_INFO("Waiting for action server to start.");
  ac_.waitForServer();  // infinite waiting untile the server is alive
  ROS_INFO("Action server started, sending goal.");
}

ActionLibAdvancedClientRos::~ActionLibAdvancedClientRos()
{
}

// main loop for the client node w.r.t the action
void ActionLibAdvancedClientRos::MainActionLoop(int nSample)
{
  // setting goal information
  custom_msg_srv_param_ros::AveragingGoal goal;
  goal.samples = nSample;
  ROS_INFO("Averaging data: size(%d)", goal.samples);

  // not use active callback to bind
  // sending the goal information to the action server
  ac_.sendGoal(goal, boost::bind(&ActionLibAdvancedClientRos::doneCb, this, _1, _2), Client::SimpleActiveCallback(),
               boost::bind(&ActionLibAdvancedClientRos::feedbackCb, this, _1));

  // wait for the action to return
  bool finished_before_timeout = ac_.waitForResult(ros::Duration(30.0));

  // result
  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = ac_.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

// Called once when the goal completes
void ActionLibAdvancedClientRos::doneCb(const actionlib::SimpleClientGoalState& state,
                                        const custom_msg_srv_param_ros::AveragingResultConstPtr& result)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
  ROS_INFO("(mean,std_dev):(%.4f,%.4f)", result->mean, result->std_dev);
  ros::shutdown();
}

// Called every time feedback is received for the goal
void ActionLibAdvancedClientRos::feedbackCb(const custom_msg_srv_param_ros::AveragingFeedbackConstPtr& feedback)
{
  ROS_INFO("Got Feedback of length %d", feedback->sample);
}