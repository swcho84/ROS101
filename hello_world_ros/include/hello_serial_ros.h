// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// using serial library
#include <serial/serial.h>

using namespace std;
using namespace ros;

class HelloSerialRos
{
public:
  HelloSerialRos();
  ~HelloSerialRos();

  void MainLoop();  

private:
  void HelloFunction();

};