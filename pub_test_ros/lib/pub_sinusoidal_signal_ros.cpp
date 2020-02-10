#include "pub_sinusoidal_signal_ros.h"

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

PubSinusoidalSignalNode::PubSinusoidalSignalNode() : nSize_(1), fSigA_(1.0), fSigB_(2.0), fSigC_(3.0)
{
  if (!ReadRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    exit(-1);
  }

  // publisher, float32 multi-array
  pubSignalArray_ = nh_.advertise<std_msgs::Float32MultiArray>(strTpNameSigInfo_, 1);
}

PubSinusoidalSignalNode::~PubSinusoidalSignalNode()
{
}

void PubSinusoidalSignalNode::MainLoop()
{
  PubSinusoidalSignal();
}

void PubSinusoidalSignalNode::PubSinusoidalSignal()
{
  // publishing float32 multi-array message
  double dSec = Time::now().toSec();
  msgSignalArray_.data.resize(nSize_);
  msgSignalArray_.data[0] = sin(Define::PI * fSigA_ * dSec);
  msgSignalArray_.data[1] = cos(Define::PI * fSigB_ * dSec);
  msgSignalArray_.data[2] = sin(-0.5 * Define::PI * fSigC_ * dSec) + cos(0.5 * Define::PI * fSigA_ * dSec);
  pubSignalArray_.publish(msgSignalArray_);
}

// reading rosparams
bool PubSinusoidalSignalNode::ReadRosParams()
{
  try
  {
    NodeHandle nh("");
    ReadRosParam(nh, "/message/sinusoidal_signal/name", strTpNameSigInfo_);
    ReadRosParam(nh, "/signal/size", nSize_);
    ReadRosParam(nh, "/signal/a", fSigA_);
    ReadRosParam(nh, "/signal/b", fSigB_);
    ReadRosParam(nh, "/signal/c", fSigC_);
  }
  catch (RosParamNotFoundException& ex)
  {
    ROS_ERROR("Failed to read param at key \"%s\"", ex.key.c_str());
    return false;
  }

  return true;
}
void PubSinusoidalSignalNode::ReadRosParam(ros::NodeHandle& nh, const string& key, float& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubSinusoidalSignalNode::ReadRosParam(ros::NodeHandle& nh, const string& key, double& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubSinusoidalSignalNode::ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubSinusoidalSignalNode::ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}
void PubSinusoidalSignalNode::ReadRosParam(ros::NodeHandle& nh, const string& key, string& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
  if (val.empty())
    throw RosParamNotFoundException(key);
}