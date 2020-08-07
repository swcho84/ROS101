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

// for using standard messages
#include <std_msgs/Float32.h>

// for using custom messages
#include <actionlib/server/simple_action_server.h>
#include <custom_msg_srv_param_ros/AveragingAction.h>

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

class ActionLibAdvancedRos
{
public:
  ActionLibAdvancedRos(std::string actionName);
  ~ActionLibAdvancedRos();

  void MainLoop();

protected:
  // node handler in class
  NodeHandle nh_;

  // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  actionlib::SimpleActionServer<custom_msg_srv_param_ros::AveragingAction> as_;

  string strAction_;
  int dataCount_, goal_;
  float sum_, sumSq_;

  custom_msg_srv_param_ros::AveragingFeedback feedback_;
  custom_msg_srv_param_ros::AveragingResult result_;

  Subscriber sub_;

private:
  void goalCB();
  void preemptCB();
  void analysisCB(const std_msgs::Float32::ConstPtr& msg);
};