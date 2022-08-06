#ifndef TURTLESIM_JOY_CTRL_CMD_ADV_JOY_XBOX360_LIB_H
#define TURTLESIM_JOY_CTRL_CMD_ADV_JOY_XBOX360_LIB_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

using namespace std;
using namespace ros;

typedef struct
{
  int nRollChannel;
  int nPitchChannel;
  int nYawChannel;
  int nThrChannel;
  float fRoll;
  float fPitch;
  float fYaw;
  float fThr;
  float fRollAxis;
  float fPitchAxis;
  float fYawAxis;
  float fThrAxis;
} CtrlAxis;

typedef struct
{
  int nRollChannel;
  int nPitchChannel;
  int nYawLtChannel;
  int nYawRtChannel;
  float fRoll;
  float fPitch;
  float fYawLt;
  float fYawRt;
  float fRollAxis;
  float fPitchAxis;
  float fYawLtAxis;
  float fYawRtAxis;
} CtrlAuxilAxis;

typedef struct
{
  int nTrigJoyCtrl;
  int nTrigAutoCtrl;
  int nTrigRgear;
  int nTrigDgear;
} CtrlButton;

typedef struct
{
  CtrlAxis ctrlMove;
  CtrlAuxilAxis ctrlAuxMove;
  CtrlButton ctrlButton;
} JoyRaw;

typedef struct
{
  CtrlAxis ctrlMove;
  CtrlAuxilAxis ctrlAuxMove;
  bool bCtrlAutoMode;
  bool bCtrlJoyMode;
  int nRgearStatus;
  int nDgearStatus;
} JoyCtrlCmd;

class JoyXBox360
{
public:
  JoyXBox360();
  ~JoyXBox360();

  JoyCtrlCmd GenJoyInfoLoop();

  double MapRange(double sourceNumber, double fromA, double fromB, double toA, double toB, int decimalPrecision);
  int sat(int nVal, int nMin, int nMax);
  float sat(float fVal, float fMin, float fMax);
  double sat(double dVal, double dMin, double dMax);	

private:
  JoyCtrlCmd joyCtrlRef_;

  Subscriber subJoyRaw_;
  Publisher pubJoyRef_;

  ros::NodeHandle nh_;

  void CbJoyRaw(const sensor_msgs::JoyConstPtr& msgRaw);
  sensor_msgs::Joy joyCurrRaw_;
  sensor_msgs::Joy joyPrevRaw_;

  JoyCtrlCmd GenJoyCtrlAxisRefInfo(sensor_msgs::Joy joyRaw, JoyCtrlCmd res);
  JoyCtrlCmd GenJoyCtrlBtnsRefInfo(sensor_msgs::Joy joyRaw, JoyCtrlCmd res);

  ros::Time rosTimeCb_;
  ros::Time rosTimeLoop_;

  int nCounterAutoJoy_;

  bool bStartCb_;
  bool bPrevUseJoyConLoop_;
  bool bPrevUseExtGuidLoop_;
};

#endif  // TURTLESIM_JOY_CTRL_CMD_ADV_JOY_XBOX360_LIB_H