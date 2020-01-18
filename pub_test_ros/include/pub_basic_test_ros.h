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

class PubBasicTestNode
{
public:
  PubBasicTestNode();
  ~PubBasicTestNode();

  void MainLoop();

private:
  void PubBasicTestFunc(string strIn, int nSize);
  
  // node handler in class
  NodeHandle nh_;

  // publisher, string
  Publisher pubHelloWorldStr_;
  std_msgs::String msgHelloWorldStr_;  

  // publisher, float32 multi-array
  Publisher pubFloat32MultiArray_;
  std_msgs::Float32MultiArray msgFloat32MultiArray_;
};