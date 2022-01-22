#ifndef JOYSTICK_101_JOY_ROTORS_POSCTRL_LIB_H
#define JOYSTICK_101_JOY_ROTORS_POSCTRL_LIB_H

#include "global_header.h"
#include "config_param.h"
#include "misc_func.h"
#include "joy_xbox360_lib.h"

using namespace std;
using namespace ros;
using namespace Eigen;

class JoyRotorSPosCtrl
{
public:
  JoyRotorSPosCtrl(const ConfigParam& cfg);
  ~JoyRotorSPosCtrl();

  void MainLoop();

private:
  ConfigParam cfgParam_;
  JoyXBox360 joyXbox360_;
  MiscFunc misc_;

  Publisher pubRotorSPosSimCtrlTrjCmd_;

  Subscriber subPoseInfo_;
  void CbPoseInfo(const geometry_msgs::PoseConstPtr& msg);
  Eigen::Vector3d mavPosEnu_;
  Eigen::Vector3d mavPosNed_;
  Eigen::Vector3d mavEulerAtt_;
  double dHeightRef_;
  double dYawAngRef_;
  double dHeadAngRef_;

  bool bYawInit_;

  geometry_msgs::PoseStamped CalcPosCtrlHeadingCmd(JoyCtrlCmd joyPosIn, geometry_msgs::PoseStamped autoPosIn);
  Vector3d CalcJoyPosCtrlCmdHeadless(JoyCtrlCmd joyPosIn, Vector3d posNedCurr, double dHeightRef, double dYawAngRef);
  Vector3d CalcJoyPosCtrlCmdHeading(JoyCtrlCmd joyPosIn, Vector3d posNedCurr, double dHeightRef, double dYawAngRef);
  Vector3d CalcJoyYawCtrlCmd(double dYawAngRef);
  geometry_msgs::PoseStamped CalcPosCtrlHeadlessCmd(JoyCtrlCmd joyPosIn, geometry_msgs::PoseStamped autoPosIn);
  void RawJoyInfo();

  JoyCtrlCmd joyRotorSPosSimCtrlCmd_;
  geometry_msgs::PoseStamped autoRotorSPoseSimCtrlCmd_;

  ros::NodeHandle nh_;
};

#endif  // JOYSTICK_101_JOY_ROTORS_POSCTRL_LIB_H