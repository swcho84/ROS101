#ifndef TURTLESIM_JOY_CTRL_CMD_ADV_TURTLESIM_CMD_PUB_LIB_H
#define TURTLESIM_JOY_CTRL_CMD_ADV_TURTLESIM_CMD_PUB_LIB_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Empty.h>

#include "joy_xbox360_lib.h"

using namespace std;
using namespace ros;

class TurtleSimCmdPubLib
{
public:
  TurtleSimCmdPubLib();
  ~TurtleSimCmdPubLib();

  void MainLoop();  

private:
  JoyXBox360 joyXbox360_;

	JoyCtrlCmd joyTurtleSimCtrlCmd_;

  ros::NodeHandle nh_;

	Publisher pubTurtleCmd_;
	ServiceClient srvClientTrjClear_;
};

#endif