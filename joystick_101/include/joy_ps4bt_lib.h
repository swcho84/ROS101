#ifndef JOYSTICK_101_JOY_PS4BT_LIB_H
#define JOYSTICK_101_JOY_PS4BT_LIB_H

#include "global_header.h"
#include "config_param.h"

using namespace std;
using namespace ros;

class JoyPS4BT
{
public:
  JoyPS4BT(const ConfigParam& cfg);
  ~JoyPS4BT();

  JoyCtrlCmd GenJoyInfoLoop();

private:
  ConfigParam cfgParam_;
  JoyCtrlCmd joyCtrlRef_;

  Subscriber subJoyRaw_;
  Publisher pubJoyRef_;

  ros::NodeHandle nh_;

  void CbJoyRaw(const sensor_msgs::JoyConstPtr& msgRaw);
  sensor_msgs::Joy joyCurrRaw_;
  sensor_msgs::Joy joyPrevRaw_;

  JoyCtrlCmd GenJoyCtrlAxisRefInfo(JoyRaw param, sensor_msgs::Joy joyRaw, JoyCtrlCmd res);
  JoyCtrlCmd GenJoyCtrlBtnsRefInfo(JoyRaw param, sensor_msgs::Joy joyRaw, JoyCtrlCmd res);

  ros::Time rosTimeCb_;
  ros::Time rosTimeLoop_;

  int nCounterAutoJoy_;

  bool bStartCb_;
  bool bPrevUseJoyConLoop_;
  bool bPrevUseExtGuidLoop_;
};

#endif  // JOYSTICK_101_JOY_PS4BT_LIB_H