#ifndef JOYSTICK_101_CONFIG_PARAM_H
#define JOYSTICK_101_CONFIG_PARAM_H

#include "global_header.h"

using namespace std;
using namespace ros;
using namespace cv;

class RosParamNotFoundException : public std::exception
{
public:
  string key;
  explicit RosParamNotFoundException(const string& key_)
  {
    key = key_;
  }
  virtual const char* what() const throw()
  {
    string msg = "Failed to read param at key ";
    return (msg + key).c_str();
  }
};

class ConfigParam
{
public:
  ConfigParam();
  ~ConfigParam();

  bool GetRosParams();

  string GenLocalTimeStringNormal();
  string GenLocalTimeStringFacet();
  double MapRange(double sourceNumber, double fromA, double fromB, double toA, double toB, int decimalPrecision);
  int sat(int nVal, int nMin, int nMax);
  float sat(float fVal, float fMin, float fMax);
  double sat(double dVal, double dMin, double dMax);

  JoyRaw joyCfgXbox;
  JoyRaw joyCfgPS4BT;
  JoyRaw joyCfgPS3BT;
  JoyRaw joyCfgLoXtrm;

  Size sizeVgaRaw;

  MoraiScale moraiSimCtrlScale;
  RotorSscale rotorScale;

  string strJoyTpNm;
  string strMoraiSimJoyCtrlTpNm;
  string strMoraiSimPoseCtrlTpNm;
  string strMoraiSimVehicleStatusTpNm;
  string strMoraiSetGearSrvNm;
  string strMoraiRawImgTpNm;
  string strMoraiObjectStatusTpNm;
  string strMoraiImgLogCmdTpNm;
  string strXPlaneJoyCtrlTpNm;
  string strRotorsJoyPosCtrlTpNm;
  string strRotorsPoseInfoTpNm;
  string strRotorsJoyPosCtrlMode;
  string strViewLinkJoyCtrlTpNm;
  string strViewLinkJoySelect;

  float fAttPsi;

  int nLogDuration;
  int nRotorSPosCtrlMode;

  double dGimbalPanRateScale;
  double dGimbalTiltRateScale;
  double dGimbalPanAngScale;
  double dGimbalTiltAngScale;

private:
  bool ReadRosParams();
  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);

  CtrlRefScale joyMoveScale_;

  string strHomeName_;
  string strRotorsJoyPosCtrlMode_;

  int nVgaWidth_;
  int nVgaHeight_;
};

#endif  // JOYSTICK_101_CONFIG_PARAM_H