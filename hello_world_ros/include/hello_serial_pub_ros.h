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

// for using standard messages
#include <std_msgs/String.h>

using namespace std;
using namespace ros;

class HelloSerialPubRos
{
public:
  HelloSerialPubRos();
  ~HelloSerialPubRos();

  bool ConnectSerialPort();

  void MainLoop();  

private:
  void HelloFunction();

  serial::Serial serialPort;
};