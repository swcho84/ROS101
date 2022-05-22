#ifndef ROS_GTEST_EXAMPLE_LIB_H
#define ROS_GTEST_EXAMPLE_LIB_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// for adding test function
#include "arithmetic_oper_lib.h"

using namespace std;
using namespace ros;

using namespace ArithOper;

class RosGtestLib
{
public:
  RosGtestLib();
  ~RosGtestLib();

  bool MainLoop(); 

private:
	ArithmeticOper ariOper_;

};

#endif  // ROS_GTEST_EXAMPLE_LIB_H
