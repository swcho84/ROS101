// using vector type data
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
#include <actionlib/server/simple_action_server.h>
#include <custom_msg_srv_param_ros/FibonacciAction.h>

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

class ActionLibBasicRos
{
public:
  ActionLibBasicRos(std::string actionName);
  ~ActionLibBasicRos();

  void MainLoop();

protected:
  // node handler in class
  NodeHandle nh_;

  // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  actionlib::SimpleActionServer<custom_msg_srv_param_ros::FibonacciAction> as_;

  // create messages that are used to published feedback/result
  custom_msg_srv_param_ros::FibonacciFeedback feedback_;
  custom_msg_srv_param_ros::FibonacciResult result_;

  string strAction_;

private:
  void CbExcute(const custom_msg_srv_param_ros::FibonacciGoalConstPtr& goal);
};