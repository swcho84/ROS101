#ifndef GTEST_SIM_H
#define GTEST_SIM_H

#include "arithmetic_oper_lib.h"
#include <gtest/gtest.h>
#include <iostream>
#include <ros/ros.h>
#include <stdlib.h>
#include <string>

#define DO_SCHEDULE(sec, expression)                                           \
  {                                                                            \
    if (sim.checkTimePassed((sec))) {                                          \
      expression;                                                              \
    }                                                                          \
  }

using namespace ArithOper;

// for using yaml-type params
// static Config GetSimConfig()
// {
//   string homedir = getenv("HOME");
//   auto config = Config(homedir +
//   "/catkin_ws/src/niv_gnc/niv_gnc/params/sim.yaml"); config.fcType =
//   "Mockup"; return config;
// }

// for using google test class
class GTestExample : public ::testing::Test {
protected:
  void SetUp() override {
    int argc = 0;
    ros::init(argc, nullptr, "ros_gtest_example_gtest");
    ros::Time::init();
    auto rate = ros::Rate(10);
    rate.sleep();
  }
};

#endif // GTEST_SIM_H