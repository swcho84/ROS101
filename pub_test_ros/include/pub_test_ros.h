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

using namespace std;
using namespace ros;

class PubTestNode
{
public:
  PubTestNode();
  ~PubTestNode();

  void PubTestFunc(string strIn, int nSize);
  void MainLoop();

  // node handler in class
  NodeHandle nh_;

  // publisher, string
  Publisher pubHelloWorldStr_;
  std_msgs::String msgHelloWorldStr_;  

  // publisher, float32 multi-array
  Publisher pubFloat32MultiArray_;
  std_msgs::Float32MultiArray msgFloat32MultiArray_;
};