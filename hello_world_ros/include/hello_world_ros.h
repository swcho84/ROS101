// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

using namespace std;
using namespace ros;

class HelloWorldRos
{
public:
  HelloWorldRos();
  ~HelloWorldRos();

  void HelloFunction(string strIn);
  void MainLoop();

  string strHello;
};