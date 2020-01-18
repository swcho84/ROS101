// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// for using custom messages
#include <custom_msg_srv_param_ros/RectArray.h>
#include <custom_msg_srv_param_ros/RectInfo.h>

// for using custom define enum variable
#include <custom_msg_srv_param_ros/Define.h>

using namespace std;
using namespace ros;

class PubAdvancedTestNode
{
public:
  PubAdvancedTestNode();
  ~PubAdvancedTestNode();

  void MainLoop();

private:
  void PubAdvancedTestFunc();
  
  // node handler in class
  NodeHandle nh_;
};