#include "sub_basic_test_ros.h"

using namespace std;
using namespace ros;

SubBasicTestNode::SubBasicTestNode()
{
  // publisher, string
  subHelloWorldStr_ = nh_.subscribe("/pub_basic_test_ros/hello_world_msg", 1, &SubBasicTestNode::currStrCbLoop, this);
  bStrCbLoop = false;

  // publisher, float32 multi-array
  subFloat32MultiArray_ =
      nh_.subscribe("/pub_basic_test_ros/arrayf32_test", 1, &SubBasicTestNode::currFloat32MtArrayCbLoop, this);
  bF32ArrayCbLoop = false;
}

SubBasicTestNode::~SubBasicTestNode()
{
}

void SubBasicTestNode::currStrCbLoop(const std_msgs::String::ConstPtr& msgRaw)
{
  msgHelloWorldStr_ = *msgRaw;
  bStrCbLoop = true;
}

void SubBasicTestNode::currFloat32MtArrayCbLoop(const std_msgs::Float32MultiArray::ConstPtr& msgRaw)
{
  msgFloat32MultiArray_ = *msgRaw;
  bF32ArrayCbLoop = true;
}

void SubBasicTestNode::MainLoop()
{
  SubBasicTestFunc();
}

void SubBasicTestNode::SubBasicTestFunc()
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