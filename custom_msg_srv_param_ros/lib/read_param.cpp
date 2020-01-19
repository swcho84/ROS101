#include "read_param.h"

using namespace std;
using namespace ros;

ReadParamTestNode::ReadParamTestNode()
{
  if (!ReadRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    exit(-1);
  }

  // for debugging
  ROS_INFO("ParamA(a,b,c)=(%.4f,%.4f,%.4f)", paramA_.fA1, paramA_.fA2, paramA_.fA3);
  ROS_INFO("ParamB(a,b,c)=(%f,%f,%f)", paramB_.dB1, paramB_.dB2, paramB_.dB3);
  ROS_INFO("ParamC(a,b,c)=(%d,%s,%d)", paramC_.nC1, paramC_.strC2.c_str(), (int)(paramC_.bC3));
  ROS_DEBUG("TopicName(RectCounter):%s", strTpNameRectCounter_.c_str());
  ROS_DEBUG("TopicName(RectInfo):%s", strTpNameRectInfo_.c_str());
}

ReadParamTestNode::~ReadParamTestNode()
{
}

void ReadParamTestNode::MainLoop()
{
  ROS_INFO_DELAYED_THROTTLE(10, "Read Custom Param from YAML file..");
}

// reading rosparams
bool ReadParamTestNode::ReadRosParams()
{
  try
  {
    NodeHandle nh("");
    ReadRosParam(nh, "/selectionA/a", paramA_.fA1);
    ReadRosParam(nh, "/selectionA/b", paramA_.fA2);
    ReadRosParam(nh, "/selectionA/c", paramA_.fA3);
    ReadRosParam(nh, "/selectionB/a", paramB_.dB1);
    ReadRosParam(nh, "/selectionB/b", paramB_.dB2);
    ReadRosParam(nh, "/selectionB/c", paramB_.dB3);
    ReadRosParam(nh, "/selectionC/a", paramC_.nC1);
    ReadRosParam(nh, "/selectionC/b", paramC_.strC2);
    ReadRosParam(nh, "/selectionC/c", paramC_.bC3);
    ReadRosParam(nh, "/message/rect_counter/name", strTpNameRectCounter_);
    ReadRosParam(nh, "/message/rect_info/name", strTpNameRectInfo_);
  }
  catch (RosParamNotFoundException& ex)
  {
    ROS_ERROR("Failed to read param at key \"%s\"", ex.key.c_str());
    return false;
  }

  return true;
}
void ReadParamTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, float& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ReadParamTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, double& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ReadParamTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ReadParamTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void ReadParamTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, string& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
  if (val.empty())
    throw RosParamNotFoundException(key);
}