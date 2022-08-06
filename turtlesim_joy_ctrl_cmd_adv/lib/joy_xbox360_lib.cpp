#include "joy_xbox360_lib.h"

using namespace std;
using namespace ros;

JoyXBox360::JoyXBox360()
{
  // generating subscriber, joy node
  subJoyRaw_ = nh_.subscribe<sensor_msgs::Joy>("/joy", 1, &JoyXBox360::CbJoyRaw, this);

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

JoyXBox360::~JoyXBox360()
{
}

// callback function, raw joystick input
void JoyXBox360::CbJoyRaw(const sensor_msgs::Joy::ConstPtr& msgRaw)
{
  joyCurrRaw_ = *msgRaw;
  rosTimeCb_ = ros::Time::now();
  bStartCb_ = true;
}

// main loop, generating the joystick control information
JoyCtrlCmd JoyXBox360::GenJoyInfoLoop()
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
  joyCtrlRef_ = GenJoyCtrlAxisRefInfo(joyCurrRaw_, joyCtrlRef_);
  joyCtrlRef_ = GenJoyCtrlBtnsRefInfo(joyCurrRaw_, joyCtrlRef_);
  return joyCtrlRef_;
}

// generating the joystick control reference information, buttons
JoyCtrlCmd JoyXBox360::GenJoyCtrlBtnsRefInfo(sensor_msgs::Joy joyRaw, JoyCtrlCmd res)
{
  if ((joyRaw.buttons[10] == 1) && (joyRaw.buttons[9] == 0))
  {
    // using guidance control input
    res.bCtrlAutoMode = true;
    res.bCtrlJoyMode = false;
  }
  else if ((joyRaw.buttons[10] == 0) && (joyRaw.buttons[9] == 1))
  {
    // using joystick control input
    res.bCtrlAutoMode = false;
    res.bCtrlJoyMode = true;
  }
  else if ((joyRaw.buttons[10] == 1) && (joyRaw.buttons[9] == 1))
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

  // assigning gear status
  res.nRgearStatus = joyRaw.buttons[4];
  res.nDgearStatus = joyRaw.buttons[5];
  return res;
}

// generating the joystick control reference information, axes
JoyCtrlCmd JoyXBox360::GenJoyCtrlAxisRefInfo(sensor_msgs::Joy joyRaw, JoyCtrlCmd res)
{
  res.ctrlMove.fRoll = (-1.0) * (joyRaw.axes[2]);
  res.ctrlMove.fPitch = (-1.0) * (joyRaw.axes[1]);
  res.ctrlMove.fYaw = (-1.0) * (joyRaw.axes[0]);
  res.ctrlMove.fThr = (1.0) * (joyRaw.axes[3]);
  res.ctrlAuxMove.fRoll += (0.01) * (-1.0) * (joyRaw.axes[6]);
  res.ctrlAuxMove.fPitch += (0.01) * (-1.0) * (joyRaw.axes[7]);
  res.ctrlAuxMove.fYawLt = (1.0) * (joyRaw.axes[5]);
  res.ctrlAuxMove.fYawRt = (1.0) * (joyRaw.axes[4]);
  res.ctrlAuxMove.fRoll = sat((res.ctrlAuxMove.fRoll), (-1.0f) * (0.01), (1.0f) * (0.01));
  res.ctrlAuxMove.fPitch = sat((res.ctrlAuxMove.fPitch), (-1.0f) * (0.01), (1.0f) * (0.01));
  res.ctrlAuxMove.fYawLt = MapRange(res.ctrlAuxMove.fYawLt, -1.0, 1.0, 1.0, 0.0, 100);
  res.ctrlAuxMove.fYawRt = MapRange(res.ctrlAuxMove.fYawRt, -1.0, 1.0, 1.0, 0.0, 100);
  return res;
}

double JoyXBox360::MapRange(double sourceNumber, double fromA, double fromB, double toA, double toB,
                            int decimalPrecision)
{
  double deltaA = fromB - fromA;
  double deltaB = toB - toA;
  double scale = deltaB / deltaA;
  double negA = -1 * fromA;
  double offset = (negA * scale) + toA;
  double finalNumber = (sourceNumber * scale) + offset;
  int calcScale = (int)(pow(10, decimalPrecision));
  return (double)(round(finalNumber * calcScale) / calcScale);
}

int JoyXBox360::sat(int nVal, int nMin, int nMax)
{
  int nRes = 0;
  if (nVal > nMax)
    nRes = nMax;
  else if (nVal < nMin)
    nRes = nMin;
  else
    nRes = nVal;
  return nRes;
}

float JoyXBox360::sat(float fVal, float fMin, float fMax)
{
  float fRes = 0.0f;
  if (fVal > fMax)
    fRes = fMax;
  else if (fVal < fMin)
    fRes = fMin;
  else
    fRes = fVal;
  return fRes;
}

double JoyXBox360::sat(double dVal, double dMin, double dMax)
{
  double dRes = 0.0;
  if (dVal > dMax)
    dRes = dMax;
  else if (dVal < dMin)
    dRes = dMin;
  else
    dRes = dVal;
  return dRes;
}
