#include "pub_basic_test_ros.h"

using namespace std;
using namespace ros;

PubBasicTestNode::PubBasicTestNode()
{
  // publisher, string
  pubHelloWorldStr_ = nh_.advertise<std_msgs::String>("/pub_basic_test_ros/hello_world_msg", 1);

  // publisher, float32 multi-array
  pubFloat32MultiArray_ = nh_.advertise<std_msgs::Float32MultiArray>("/pub_basic_test_ros/arrayf32_test", 1);
}

PubBasicTestNode::~PubBasicTestNode()
{
}

void PubBasicTestNode::MainLoop()
{
  int nSize = 6;
  string strHello;
  strHello = "Hello, ROS world!";

  PubBasicTestFunc(strHello, nSize);
}

void PubBasicTestNode::PubBasicTestFunc(string strIn, int nSize)
{
  // publishing string data
  msgHelloWorldStr_.data = strIn.c_str();
  pubHelloWorldStr_.publish(msgHelloWorldStr_);

  // publishing float32 multi-array data
  msgFloat32MultiArray_.data.resize(nSize);
  for (unsigned int i = 0; i < nSize; i++)
  {
    msgFloat32MultiArray_.data[i] = i;
  }
  pubFloat32MultiArray_.publish(msgFloat32MultiArray_);
}