#ifndef JOYSTICK_101_JOY_VIEWLINK_CTRL_LIB_H
#define JOYSTICK_101_JOY_VIEWLINK_CTRL_LIB_H

#include "global_header.h"
#include "config_param.h"
#include "joy_xbox360_lib.h"
#include "joy_logi_extream_lib.h"

using namespace std;
using namespace ros;

class JoyViewLinkCtrl
{
public:
  JoyViewLinkCtrl(const ConfigParam& cfg);
  ~JoyViewLinkCtrl();

  void MainLoop();

private:
  ConfigParam cfgParam_;
  JoyXBox360 joyXbox360_;
  JoyLogiExtream joyLogiExtream_;

  ros::NodeHandle nh_;

  Publisher pubViewLinkJoyCtrlCmd_;

  JoyCtrlCmd joyViewLinkCtrlCmd_;
};

#endif  // JOYSTICK_101_JOY_VIEWLINK_CTRL_LIB_H