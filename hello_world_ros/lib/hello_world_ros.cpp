#include "hello_world_ros.h"

using namespace std;
using namespace ros;

HelloWorldRos::HelloWorldRos()
{
  strHello_ = "Hello, ROS world!";
}

HelloWorldRos::~HelloWorldRos()
{
}

void HelloWorldRos::MainLoop()
{
  HelloFunction(strHello_);
}

void HelloWorldRos::HelloFunction(string strIn)
{
  // default rate
  ROS_INFO("info %s", strIn.c_str());
  ROS_DEBUG("debug %s", strIn.c_str());
  ROS_WARN("warn %s", strIn.c_str());
  ROS_ERROR("error %s", strIn.c_str());
  ROS_FATAL("fatal %s", strIn.c_str());

  // delayed rate (higher value is slow printing performance)
  // ROS_INFO_DELAYED_THROTTLE(5, "delayed info %s", strIn.c_str());
  // ROS_DEBUG_DELAYED_THROTTLE(5, "delayed debug %s", strIn.c_str());
  // ROS_WARN_DELAYED_THROTTLE(5, "delayed warn %s", strIn.c_str());
  // ROS_ERROR_DELAYED_THROTTLE(5, "delayed error %s", strIn.c_str());
  // ROS_FATAL_DELAYED_THROTTLE(5, "delayed fatal %s", strIn.c_str());
}