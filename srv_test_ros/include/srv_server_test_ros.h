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
#include "srv_test_ros/AddTwoInts.h"
#include "srv_test_ros/SetMissionInfo.h"

#define PI    3.14159265359
#define D2R   PI/180.0
#define R2D   180.0/PI  

using namespace std;
using namespace ros;

class SrvServerTestNode
{
public:
  SrvServerTestNode();
  ~SrvServerTestNode();

  void MainLoop();

private:
  bool CalcAddSrv(srv_test_ros::AddTwoInts::Request& req, srv_test_ros::AddTwoInts::Response& res);
  bool SetMissionInfoSrv(srv_test_ros::SetMissionInfo::Request& req, srv_test_ros::SetMissionInfo::Response& res);

  // node handler in class
  NodeHandle nh_;

  ServiceServer srvServerCalcAdd_;
  ServiceServer srvServerSetMissionInfo_;
};