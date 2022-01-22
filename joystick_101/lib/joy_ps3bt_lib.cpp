#include "joy_ps3bt_lib.h"

using namespace std;
using namespace ros;

JoyPS3BT::JoyPS3BT(const ConfigParam& cfg) : cfgParam_(cfg)
{
  // generating subscriber, joy node
  subJoyRaw_ = nh_.subscribe<sensor_msgs::Joy>(cfgParam_.strJoyTpNm, 1, &JoyPS3BT::CbJoyRaw, this);

  // setting the callback startup flag
  bStartCb_ = false;

  // setting the initialized value
  joyCtrlRef_.ctrlAuxMove.fRoll = 0.0f;
  joyCtrlRef_.ctrlAuxMove.fPitch = 0.0f;
  joyCtrlRef_.ctrlAuxMove.fYawLt = 0.0f;
  joyCtrlRef_.ctrlAuxMove.fYawRt = 0.0f;
  bPrevUseExtGuidLoop_ = false;
  bPrevUseJoyConLoop_ = true;
  nCounterAutoJoy_ = 0;
}

JoyPS3BT::~JoyPS3BT()
{
}

// callback function, raw joystick input
void JoyPS3BT::CbJoyRaw(const sensor_msgs::Joy::ConstPtr& msgRaw)
{
  joyCurrRaw_ = *msgRaw;
  rosTimeCb_ = ros::Time::now();
  bStartCb_ = true;
}

// main loop, generating the joystick control information
JoyCtrlCmd JoyPS3BT::GenJoyInfoLoop()
{
  // if the callback startup flag is false, just pass the loop
  if (!bStartCb_)
    return joyCtrlRef_;

  // calculating the time difference
  rosTimeLoop_ = ros::Time::now();
  double dTimeDiff = (rosTimeLoop_ - rosTimeCb_).toSec();

  // setting the curr. or prev. joy status (param: 0.5 [sec])
  if (dTimeDiff > 0.5)
    joyCurrRaw_ = joyPrevRaw_;
  else
    joyPrevRaw_ = joyCurrRaw_;

  // generating the joystick control reference information, axes and buttons
  joyCtrlRef_ = GenJoyCtrlAxisRefInfo(cfgParam_.joyCfgPS3BT, joyCurrRaw_, joyCtrlRef_);
  joyCtrlRef_ = GenJoyCtrlBtnsRefInfo(cfgParam_.joyCfgPS3BT, joyCurrRaw_, joyCtrlRef_);
  return joyCtrlRef_;
}

// generating the joystick control reference information, buttons
JoyCtrlCmd JoyPS3BT::GenJoyCtrlBtnsRefInfo(JoyRaw param, sensor_msgs::Joy joyRaw, JoyCtrlCmd res)
{
  if ((joyRaw.buttons[param.ctrlButton.nTrigAutoCtrl] == 1) && (joyRaw.buttons[param.ctrlButton.nTrigJoyCtrl] == 0))
  {
    // using guidance control input
    res.bCtrlAutoMode = true;
    res.bCtrlJoyMode = false;
  }
  else if ((joyRaw.buttons[param.ctrlButton.nTrigAutoCtrl] == 0) &&
           (joyRaw.buttons[param.ctrlButton.nTrigJoyCtrl] == 1))
  {
    // using joystick control input
    res.bCtrlAutoMode = false;
    res.bCtrlJoyMode = true;
  }
  else if ((joyRaw.buttons[param.ctrlButton.nTrigAutoCtrl] == 1) &&
           (joyRaw.buttons[param.ctrlButton.nTrigJoyCtrl] == 1))
  {
    // default: using joystick control input
    res.bCtrlAutoMode = false;
    res.bCtrlJoyMode = true;
  }
  else
  {
    // staying the flag type
    res.bCtrlAutoMode = bPrevUseExtGuidLoop_;
    res.bCtrlJoyMode = bPrevUseJoyConLoop_;
  }

  // saving the previous data
  bPrevUseExtGuidLoop_ = res.bCtrlAutoMode;
  bPrevUseJoyConLoop_ = res.bCtrlJoyMode;
  return res;
}

// generating the joystick control reference information, axes
JoyCtrlCmd JoyPS3BT::GenJoyCtrlAxisRefInfo(JoyRaw param, sensor_msgs::Joy joyRaw, JoyCtrlCmd res)
{
  res.ctrlMove.fRoll = (param.ctrlMove.fRollAxis) * (joyRaw.axes[param.ctrlMove.nRollChannel]);
  res.ctrlMove.fPitch = (param.ctrlMove.fPitchAxis) * (joyRaw.axes[param.ctrlMove.nPitchChannel]);
  res.ctrlMove.fYaw = (param.ctrlMove.fYawAxis) * (joyRaw.axes[param.ctrlMove.nYawChannel]);
  res.ctrlMove.fThr = (param.ctrlMove.fThrAxis) * (joyRaw.axes[param.ctrlMove.nThrChannel]);
  res.ctrlScale = param.ctrlScale;
  return res;
}