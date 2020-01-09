#include "hello_world_ros.h"

using namespace std;
using namespace ros;

HelloWorldRos::HelloWorldRos()
{
}

HelloWorldRos::~HelloWorldRos()
{
}

void HelloWorldRos::MainLoop()
{
  string strHello;
  strHello = "Hello, ROS world!";
  HelloFunction(strHello);  
}

void HelloWorldRos::HelloFunction(string strIn)
{
  ROS_INFO("%s", strIn.c_str());
}