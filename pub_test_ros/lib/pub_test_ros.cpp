#include "pub_test_ros.h"

using namespace std;
using namespace ros;

PubTestNode::PubTestNode()
{
  // publisher, string
  pubHelloWorldStr_ = nh_.advertise<std_msgs::String>("/pub_test_ros/hello_world_msg", 1);

  // publisher, float32 multi-array
  pubFloat32MultiArray_ = nh_.advertise<std_msgs::Float32MultiArray>("/pub_test_ros/arrayf32_test", 1);
}

PubTestNode::~PubTestNode()
{
}

void PubTestNode::MainLoop()
{
  int nSize = 6;
  string strHello;
  strHello = "Hello, ROS world!";

  PubTestFunc(strHello, nSize);
}

void PubTestNode::PubTestFunc(string strIn, int nSize)
{
  // publishing string data
  msgHelloWorldStr_.data = strIn.c_str();
  pubHelloWorldStr_.publish(msgHelloWorldStr_);

  // publishing float32 multi-array data
  msgFloat32MultiArray_.data.resize(nSize);
  for (int i = 0; i < nSize; i++)
  {
    msgFloat32MultiArray_.data[i] = i;
  }
  pubFloat32MultiArray_.publish(msgFloat32MultiArray_);
}