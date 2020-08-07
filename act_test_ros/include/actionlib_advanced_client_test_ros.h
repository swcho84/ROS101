#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <signal.h>

// for using boost library
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

// essential header for ROS operation
#include <ros/ros.h>

// for using custom messages
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <custom_msg_srv_param_ros/AveragingAction.h>

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

typedef actionlib::SimpleActionClient<custom_msg_srv_param_ros::AveragingAction> Client;

class ActionLibAdvancedClientRos
{
public:
  ActionLibAdvancedClientRos(std::string actionName);
  ~ActionLibAdvancedClientRos();

  void MainActionLoop(int order);

private:
  Client ac_;

  void doneCb(const actionlib::SimpleClientGoalState& state,
              const custom_msg_srv_param_ros::AveragingResultConstPtr& result);
  void feedbackCb(const custom_msg_srv_param_ros::AveragingFeedbackConstPtr& feedback);
};