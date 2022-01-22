#ifndef JOYSTICK_101_JOY_TEST_LIB_H
#define JOYSTICK_101_JOY_TEST_LIB_H

#include "global_header.h"
#include "config_param.h"
#include "joy_xbox360_lib.h"
#include "joy_ps4bt_lib.h"
#include "joy_ps3bt_lib.h"
#include "joy_logi_extream_lib.h"

using namespace std;
using namespace ros;

class JoyTest
{
public:
  JoyTest(const ConfigParam& cfg);
  ~JoyTest();

  void MainLoop();

private:
  ConfigParam cfgParam_;
  JoyXBox360 joyXbox360_;
  JoyPS4BT joyPs4Bt_;
  JoyPS3BT joyPs3Bt_;
  JoyLogiExtream joyLogiExtream_;

  ros::NodeHandle nh_;
};

#endif  // JOYSTICK_101_JOY_TEST_LIB_H