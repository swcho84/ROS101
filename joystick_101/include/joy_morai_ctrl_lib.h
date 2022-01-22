#ifndef JOYSTICK_101_JOY_MORAI_CTRL_LIB_H
#define JOYSTICK_101_JOY_MORAI_CTRL_LIB_H

#include "global_header.h"
#include "config_param.h"
#include "joy_xbox360_lib.h"
#include "morai_sim_auto_log_lib.h"

using namespace std;
using namespace ros;

class JoyMoraiCtrl
{
public:
  JoyMoraiCtrl(const ConfigParam& cfg);
  ~JoyMoraiCtrl();

  void MainLoop(double dt);

private:
  ConfigParam cfgParam_;
  JoyXBox360 joyXbox360_;
  MoraiAutoLog moraiAutoLog_;

  ServiceClient srvClientSetGearInfo_;

  Publisher pubMoraiSimCtrlCmd_;
  Publisher pubMoraiSimPoseCmd_;

  Subscriber subMoraiSimVehicleStatus_;
  void CbMoraiVehicleStatus(const morai_msgs::EgoVehicleStatus::ConstPtr& msgRaw);
  morai_msgs::EgoVehicleStatus msgEgoVehicleStatus_;

  Subscriber subMoraiObjectStatus_;
  void CbMoraiObjectStatus(const morai_msgs::ObjectStatusList::ConstPtr& msgRaw);
  morai_msgs::ObjectStatusList msgObjectStatusList_;

  Subscriber subMoraiSimRosBagImgLog_;
  void CbMoraiImgLogCmdtatus(const std_msgs::UInt8::ConstPtr& msgRaw);
  std_msgs::UInt8 msgImgLogCmd_;
  int nDbTotalLogSize_;
  int nDbCurrLogSize_;

  void CbRawImgData(const sensor_msgs::ImageConstPtr& msgRaw);
  image_transport::Subscriber subRawImg_;
  cv_bridge::CvImagePtr cvPtrImgSrc_;
  bool bStartImgCallBack_;
  Mat imgSrc_;

  void GenShutterJoyCmd(float shutter, double dt);
  void GenShutterAutoCmd();
  void SendKey(Display* disp, KeySym keysym, KeySym modsym);
  Display* disp_;

  bool bEgoVehicleStatus_;
  bool bEgoVehiclePoseCalStatus_;
  bool bObjectStatusList_;
  bool bImgLogStatus_;
  int nGearDRstatus_;
  float fShutterCmd_;
  double dTimeCounter_;
  double dTimeSaver_;

  JoyCtrlCmd joyMoraiSimCtrlCmd_;

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
};

#endif  // JOYSTICK_101_JOY_MORAI_CTRL_LIB_H