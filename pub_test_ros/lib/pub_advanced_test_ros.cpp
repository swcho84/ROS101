#include "pub_advanced_test_ros.h"

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

PubAdvancedTestNode::PubAdvancedTestNode()
: nRectSize_(0)
{
  if (!ReadRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    exit(-1);
  }

  // publisher, custom msg
  pubRectArray_ = nh_.advertise<RectArray>(strTpNameRectInfo_, 1);
}

PubAdvancedTestNode::~PubAdvancedTestNode()
{
}

void PubAdvancedTestNode::MainLoop()
{
  PubAdvancedTestFunc();
}

void PubAdvancedTestNode::PubAdvancedTestFunc()
{
  // publishing custom msg with vector type
  msgRectArray_.vecRectArray.clear();
  for (unsigned int i = 0; i < nRectSize_; i++)
  {
    RectInfo msgRectInfoTemp_;
    msgRectInfoTemp_.nNum = i;
    msgRectInfoTemp_.fXlt = (float)((10.0f) * (i));
    msgRectInfoTemp_.fYlt = (float)((20.0f) * (i));
    msgRectInfoTemp_.fWidth = (float)((30.0f) * (i));
    msgRectInfoTemp_.fHeight = (float)((40.0f) * (i));
    msgRectInfoTemp_.fScore = (float)((50.0f) * (i));
    msgRectArray_.vecRectArray.push_back(msgRectInfoTemp_);
  }
  msgRectArray_.bDetect = true;

  switch(nRectType_)
  {
    case Define::STATUS_A:
    {
      msgRectArray_.nStatus = Define::STATUS_A;
      break;
    }
    case Define::STATUS_B:
    {
      msgRectArray_.nStatus = Define::STATUS_B;
      break;
    }
    case Define::STATUS_C:
    {
      msgRectArray_.nStatus = Define::STATUS_C;
      break;
    }
    default:
    {
      msgRectArray_.nStatus = Define::STATUS_DEFAULT;
      break;
    }        
  }  

  pubRectArray_.publish(msgRectArray_);
}

// reading rosparams
bool PubAdvancedTestNode::ReadRosParams()
{
  try
  {
    NodeHandle nh("");
    ReadRosParam(nh, "/message/rect_info/name", strTpNameRectInfo_);
    ReadRosParam(nh, "/rect/size", nRectSize_);
    ReadRosParam(nh, "/rect/type", nRectType_);
  }
  catch (RosParamNotFoundException& ex)
  {
    ROS_ERROR("Failed to read param at key \"%s\"", ex.key.c_str());
    return false;
  }

  return true;
}
void PubAdvancedTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, float& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubAdvancedTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, double& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubAdvancedTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubAdvancedTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubAdvancedTestNode::ReadRosParam(ros::NodeHandle& nh, const string& key, string& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
  if (val.empty())
    throw RosParamNotFoundException(key);
}