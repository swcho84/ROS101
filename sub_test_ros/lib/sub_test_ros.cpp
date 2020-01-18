#include "sub_test_ros.h"

using namespace std;
using namespace ros;

SubTestNode::SubTestNode()
{
  // publisher, string
  subHelloWorldStr_ = nh_.subscribe("/pub_test_ros/hello_world_msg", 1, &SubTestNode::currStrCbLoop, this);
  bStrCbLoop = false;

  // publisher, float32 multi-array
  subFloat32MultiArray_ = nh_.subscribe("/pub_test_ros/arrayf32_test", 1, &SubTestNode::currF32ArrayCbLoop, this);
  bF32ArrayCbLoop = false;
}

SubTestNode::~SubTestNode()
{
}

void SubTestNode::currStrCbLoop(const std_msgs::String::ConstPtr& msgRaw)
{
  msgHelloWorldStr_ = *msgRaw;
  bStrCbLoop = true;
}

void SubTestNode::currF32ArrayCbLoop(const std_msgs::Float32MultiArray::ConstPtr& msgRaw)
{
  msgFloat32MultiArray_ = *msgRaw;
  bF32ArrayCbLoop = true;
}

void SubTestNode::MainLoop()
{
  SubTestFunc();
}

void SubTestNode::SubTestFunc()
{
  if (bStrCbLoop)
  {
    ROS_DEBUG("info %s", msgHelloWorldStr_.data.c_str());
    bStrCbLoop = false;
  }

  if (bF32ArrayCbLoop)
  {
    for (unsigned int i = 0; i < msgFloat32MultiArray_.data.size(); i++)
    {
      ROS_INFO("data[%d]=%.4f", i, msgFloat32MultiArray_.data[i]);
    }
    bF32ArrayCbLoop = false;
  }
}