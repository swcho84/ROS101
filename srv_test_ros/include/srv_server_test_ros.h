// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// for using standard messages
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/String.h>

// for using service messages
#include "custom_msg_srv_param_ros/AddTwoInts.h"
#include "custom_msg_srv_param_ros/SetMissionInfo.h"

// for using custom define enum variable
#include <custom_msg_srv_param_ros/Define.h>

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

class SrvServerTestNode
{
public:
  SrvServerTestNode();
  ~SrvServerTestNode();

  void MainLoop();

private:
  bool CalcAddSrv(AddTwoInts::Request& req, AddTwoInts::Response& res);
  bool SetMissionInfoSrv(SetMissionInfo::Request& req, SetMissionInfo::Response& res);

  // node handler in class
  NodeHandle nh_;

  ServiceServer srvServerCalcAdd_;
  ServiceServer srvServerSetMissionInfo_;
};