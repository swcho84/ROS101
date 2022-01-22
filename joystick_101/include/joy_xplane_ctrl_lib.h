#ifndef JOYSTICK_101_JOY_XPLANE_CTRL_LIB_H
#define JOYSTICK_101_JOY_XPLANE_CTRL_LIB_H

#include "global_header.h"
#include "config_param.h"
#include "joy_logi_extream_lib.h"

using namespace std;
using namespace ros;

class JoyXPlaneCtrl
{
public:
  JoyXPlaneCtrl(const ConfigParam& cfg);
  ~JoyXPlaneCtrl();

  void MainLoop();

private:
  ConfigParam cfgParam_;
  JoyLogiExtream joyLogiExtream_;

  Publisher pubXPlaneJoySimCtrlCmd_;

  JoyCtrlCmd joyXPlaneJoySimCtrlCmd_;

  ros::NodeHandle nh_;
};

#endif  // JOYSTICK_101_JOY_XPLANE_CTRL_LIB_H