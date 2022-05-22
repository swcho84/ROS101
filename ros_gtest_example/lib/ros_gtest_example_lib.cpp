#include "ros_gtest_example_lib.h"

using namespace std;
using namespace ros;

RosGtestLib::RosGtestLib() {}

RosGtestLib::~RosGtestLib() {}

bool RosGtestLib::MainLoop() {
  bool bRes = false;

  ROS_INFO("TestAddFunc:1+2=%d", ariOper_.CalcAddNum(1, 2));
  if (ariOper_.CalcAddNum(1, 2) == 3)
    bRes = true;

  return bRes;
}