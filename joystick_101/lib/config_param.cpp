#include "config_param.h"

using namespace std;
using namespace ros;

ConfigParam::ConfigParam()
{
  nVgaWidth_ = 640;
  nVgaHeight_ = 480;
  sizeVgaRaw = Size(nVgaWidth_, nVgaHeight_);
}

ConfigParam::~ConfigParam()
{
}

// reading rosparams (public function)
bool ConfigParam::GetRosParams()
{
  return ReadRosParams();
}

// reading rosparams (private function)
bool ConfigParam::ReadRosParams()
{
  try
  {
    NodeHandle nh("");

    // general information
    strHomeName_ = getenv("HOME");

    // reading parameters
    ReadRosParam(nh, "/Joystick/joyTopicName", strJoyTpNm);
    ReadRosParam(nh, "/Joystick/moraiCtrlTopicName", strMoraiSimJoyCtrlTpNm);
    ReadRosParam(nh, "/Joystick/moraiPoseTopicName", strMoraiSimPoseCtrlTpNm);
    ReadRosParam(nh, "/Joystick/moraiEgoVehicleStatusTopicName", strMoraiSimVehicleStatusTpNm);
    ReadRosParam(nh, "/Joystick/moraiSetGearSrvName", strMoraiSetGearSrvNm);
    ReadRosParam(nh, "/Joystick/moraiRawImgTopicName", strMoraiRawImgTpNm);
    ReadRosParam(nh, "/Joystick/moraiObjectStatusTopicName", strMoraiObjectStatusTpNm);
    ReadRosParam(nh, "/Joystick/moraiImgLogCmdTopicName", strMoraiImgLogCmdTpNm);
    ReadRosParam(nh, "/Joystick/xplaneCtrlTopicName", strXPlaneJoyCtrlTpNm);
    ReadRosParam(nh, "/Joystick/rotorsJoyPosCtrlTopicName", strRotorsJoyPosCtrlTpNm);
    ReadRosParam(nh, "/Joystick/rotorsPoseInfoTopicName", strRotorsPoseInfoTpNm);
    ReadRosParam(nh, "/Joystick/rotorsJoyPosCtrlMode", strRotorsJoyPosCtrlMode_);

    if (strRotorsJoyPosCtrlMode_ == "heading")
      nRotorSPosCtrlMode = ROTORSHEADINGCTRL;
    else
      nRotorSPosCtrlMode = ROTORSHEADLESSCTRL;

    ReadRosParam(nh, "/Joystick/imgLogRef/logDuration", nLogDuration);
    ReadRosParam(nh, "/Joystick/imgLogRef/headDiff", fDiffHeadRef);
    ReadRosParam(nh, "/Joystick/imgLogRef/centerObjNum", nCenterObjNum);
    ReadRosParam(nh, "/Joystick/imgLogRef/centerPedNum", nCenterPedNum);
    ReadRosParam(nh, "/Joystick/imgLogRef/signSet", fSignRef);

    ReadRosParam(nh, "/Joystick/commandParam/scaleRPAtt/roll", joyMoveScale_.fAttPhi);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRPAtt/pitch", joyMoveScale_.fAttTheta);
    ReadRosParam(nh, "/Joystick/commandParam/scaleYawRate", joyMoveScale_.fAttRatePsi);
    ReadRosParam(nh, "/Joystick/commandParam/scaleHeaveVel", joyMoveScale_.fVelHeave);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRPAuxAttAccum/roll", joyMoveScale_.fPhiAuxAccumScale);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRPAuxAttAccum/pitch", joyMoveScale_.fThetaAuxAccumScale);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRPAuxAttMax/roll", joyMoveScale_.fPhiAuxAccumMax);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRPAuxAttMax/pitch", joyMoveScale_.fThetaAuxAccumMax);
    ReadRosParam(nh, "/Joystick/commandParam/scaleYawAuxMinMaxResol/min", joyMoveScale_.fPsiAuxMin);
    ReadRosParam(nh, "/Joystick/commandParam/scaleYawAuxMinMaxResol/max", joyMoveScale_.fPsiAuxMax);
    ReadRosParam(nh, "/Joystick/commandParam/scaleYawAuxMinMaxResol/resol", joyMoveScale_.nPsiResol);
    ReadRosParam(nh, "/Joystick/commandParam/scaleThrottleMinMaxResol/min", joyMoveScale_.fThrAuxMin);
    ReadRosParam(nh, "/Joystick/commandParam/scaleThrottleMinMaxResol/max", joyMoveScale_.fThrAuxMax);
    ReadRosParam(nh, "/Joystick/commandParam/scaleThrottleMinMaxResol/resol", joyMoveScale_.nThrResol);
    ReadRosParam(nh, "/Joystick/commandParam/scaleYawAtt/yaw", fAttPsi);
    ReadRosParam(nh, "/Joystick/commandParam/scaleMorai/fwdvel", moraiSimCtrlScale.fFwdVel);
    ReadRosParam(nh, "/Joystick/commandParam/scaleMorai/steer", moraiSimCtrlScale.fSteer);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRotorS/heightPosAccum", rotorScale.fHeightAccum);
    ReadRosParam(nh, "/Joystick/commandParam/scaleRotorS/yawAng", rotorScale.fYawAng);
    // fAttPsi = (fAttPsi) * (D2R);
    // joyMoveScale_.fAttPhi = (joyMoveScale_.fAttPhi) * (D2R);
    // joyMoveScale_.fAttTheta = (joyMoveScale_.fAttTheta) * (D2R);
    // joyMoveScale_.fAttRatePsi = (joyMoveScale_.fAttRatePsi) * (D2R);
    moraiSimCtrlScale.fFwdVel = (moraiSimCtrlScale.fFwdVel) * (MPS2KMPH);
    moraiSimCtrlScale.fSteer = (moraiSimCtrlScale.fSteer) * (D2R);

    // reading parameters, w.r.t the xbox360 wired controller
    ReadRosParam(nh, "/Joystick/XBox360/channel/roll", joyCfgXbox.ctrlMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/XBox360/channel/pitch", joyCfgXbox.ctrlMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/XBox360/channel/yaw", joyCfgXbox.ctrlMove.nYawChannel);
    ReadRosParam(nh, "/Joystick/XBox360/channel/throttle", joyCfgXbox.ctrlMove.nThrChannel);
    ReadRosParam(nh, "/Joystick/XBox360/auxil/channel/roll", joyCfgXbox.ctrlAuxMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/XBox360/auxil/channel/pitch", joyCfgXbox.ctrlAuxMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/XBox360/auxil/channel/yawleft", joyCfgXbox.ctrlAuxMove.nYawLtChannel);
    ReadRosParam(nh, "/Joystick/XBox360/auxil/channel/yawright", joyCfgXbox.ctrlAuxMove.nYawRtChannel);
    ReadRosParam(nh, "/Joystick/XBox360/auxil/direction/yawleft", joyCfgXbox.ctrlAuxMove.fYawLtAxis);
    ReadRosParam(nh, "/Joystick/XBox360/auxil/direction/yawright", joyCfgXbox.ctrlAuxMove.fYawRtAxis);
    ReadRosParam(nh, "/Joystick/XBox360/direction/roll", joyCfgXbox.ctrlMove.fRollAxis);
    ReadRosParam(nh, "/Joystick/XBox360/direction/pitch", joyCfgXbox.ctrlMove.fPitchAxis);
    ReadRosParam(nh, "/Joystick/XBox360/direction/yaw", joyCfgXbox.ctrlMove.fYawAxis);
    ReadRosParam(nh, "/Joystick/XBox360/direction/throttle", joyCfgXbox.ctrlMove.fThrAxis);
    ReadRosParam(nh, "/Joystick/XBox360/button/triggerAuto", joyCfgXbox.ctrlButton.nTrigAutoCtrl);
    ReadRosParam(nh, "/Joystick/XBox360/button/triggerJoy", joyCfgXbox.ctrlButton.nTrigJoyCtrl);
    ReadRosParam(nh, "/Joystick/XBox360/button/triggerRgear", joyCfgXbox.ctrlButton.nTrigRgear);
    ReadRosParam(nh, "/Joystick/XBox360/button/triggerDgear", joyCfgXbox.ctrlButton.nTrigDgear);
    joyCfgXbox.ctrlAuxMove.fRollAxis = joyCfgXbox.ctrlMove.fRollAxis;
    joyCfgXbox.ctrlAuxMove.fPitchAxis = joyCfgXbox.ctrlMove.fPitchAxis;
    joyCfgXbox.ctrlScale = joyMoveScale_;

    // reading parameters, w.r.t the ps4 bluetooth wireless controller
    ReadRosParam(nh, "/Joystick/PS4BT/channel/roll", joyCfgPS4BT.ctrlMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/channel/pitch", joyCfgPS4BT.ctrlMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/channel/yaw", joyCfgPS4BT.ctrlMove.nYawChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/channel/throttle", joyCfgPS4BT.ctrlMove.nThrChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/auxil/channel/roll", joyCfgPS4BT.ctrlAuxMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/auxil/channel/pitch", joyCfgPS4BT.ctrlAuxMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/auxil/channel/yawleft", joyCfgPS4BT.ctrlAuxMove.nYawLtChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/auxil/channel/yawright", joyCfgPS4BT.ctrlAuxMove.nYawRtChannel);
    ReadRosParam(nh, "/Joystick/PS4BT/auxil/direction/yawleft", joyCfgPS4BT.ctrlAuxMove.fYawLtAxis);
    ReadRosParam(nh, "/Joystick/PS4BT/auxil/direction/yawright", joyCfgPS4BT.ctrlAuxMove.fYawRtAxis);
    ReadRosParam(nh, "/Joystick/PS4BT/direction/roll", joyCfgPS4BT.ctrlMove.fRollAxis);
    ReadRosParam(nh, "/Joystick/PS4BT/direction/pitch", joyCfgPS4BT.ctrlMove.fPitchAxis);
    ReadRosParam(nh, "/Joystick/PS4BT/direction/yaw", joyCfgPS4BT.ctrlMove.fYawAxis);
    ReadRosParam(nh, "/Joystick/PS4BT/direction/throttle", joyCfgPS4BT.ctrlMove.fThrAxis);
    ReadRosParam(nh, "/Joystick/PS4BT/button/triggerAuto", joyCfgPS4BT.ctrlButton.nTrigAutoCtrl);
    ReadRosParam(nh, "/Joystick/PS4BT/button/triggerJoy", joyCfgPS4BT.ctrlButton.nTrigJoyCtrl);
    joyCfgPS4BT.ctrlAuxMove.fRollAxis = joyCfgPS4BT.ctrlMove.fRollAxis;
    joyCfgPS4BT.ctrlAuxMove.fPitchAxis = joyCfgPS4BT.ctrlMove.fPitchAxis;
    joyCfgPS4BT.ctrlScale = joyMoveScale_;

    // reading parameters, w.r.t the ps3 bluetooth wireless controller
    ReadRosParam(nh, "/Joystick/PS3BT/channel/roll", joyCfgPS3BT.ctrlMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/PS3BT/channel/pitch", joyCfgPS3BT.ctrlMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/PS3BT/channel/yaw", joyCfgPS3BT.ctrlMove.nYawChannel);
    ReadRosParam(nh, "/Joystick/PS3BT/channel/throttle", joyCfgPS3BT.ctrlMove.nThrChannel);
    ReadRosParam(nh, "/Joystick/PS3BT/direction/roll", joyCfgPS3BT.ctrlMove.fRollAxis);
    ReadRosParam(nh, "/Joystick/PS3BT/direction/pitch", joyCfgPS3BT.ctrlMove.fPitchAxis);
    ReadRosParam(nh, "/Joystick/PS3BT/direction/yaw", joyCfgPS3BT.ctrlMove.fYawAxis);
    ReadRosParam(nh, "/Joystick/PS3BT/direction/throttle", joyCfgPS3BT.ctrlMove.fThrAxis);
    ReadRosParam(nh, "/Joystick/PS3BT/button/triggerAuto", joyCfgPS3BT.ctrlButton.nTrigAutoCtrl);
    ReadRosParam(nh, "/Joystick/PS3BT/button/triggerJoy", joyCfgPS3BT.ctrlButton.nTrigJoyCtrl);
    joyCfgPS3BT.ctrlAuxMove.fRollAxis = joyCfgPS3BT.ctrlMove.fRollAxis;
    joyCfgPS3BT.ctrlAuxMove.fPitchAxis = joyCfgPS3BT.ctrlMove.fPitchAxis;
    joyCfgPS3BT.ctrlScale = joyMoveScale_;

    // reading parameters, w.r.t the logitech extream controller
    ReadRosParam(nh, "/Joystick/LogiTechExtream/channel/roll", joyCfgLoXtrm.ctrlMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/channel/pitch", joyCfgLoXtrm.ctrlMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/channel/yaw", joyCfgLoXtrm.ctrlMove.nYawChannel);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/channel/throttle", joyCfgLoXtrm.ctrlMove.nThrChannel);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/auxil/channel/roll", joyCfgLoXtrm.ctrlAuxMove.nRollChannel);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/auxil/channel/pitch", joyCfgLoXtrm.ctrlAuxMove.nPitchChannel);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/direction/roll", joyCfgLoXtrm.ctrlMove.fRollAxis);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/direction/pitch", joyCfgLoXtrm.ctrlMove.fPitchAxis);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/direction/yaw", joyCfgLoXtrm.ctrlMove.fYawAxis);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/direction/throttle", joyCfgLoXtrm.ctrlMove.fThrAxis);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/button/triggerAuto", joyCfgLoXtrm.ctrlButton.nTrigAutoCtrl);
    ReadRosParam(nh, "/Joystick/LogiTechExtream/button/triggerJoy", joyCfgLoXtrm.ctrlButton.nTrigJoyCtrl);
    joyCfgLoXtrm.ctrlAuxMove.fRollAxis = joyCfgLoXtrm.ctrlMove.fRollAxis;
    joyCfgLoXtrm.ctrlAuxMove.fPitchAxis = joyCfgLoXtrm.ctrlMove.fPitchAxis;
    joyCfgLoXtrm.ctrlScale = joyMoveScale_;
  }
  catch (RosParamNotFoundException& ex)
  {
    ROS_ERROR("Failed to read param at key \"%s\"", ex.key.c_str());
    return false;
  }

  return true;
}

// generating local time to string with facet
string ConfigParam::GenLocalTimeStringFacet()
{
  std::stringstream ss;
  boost::local_time::local_date_time currentTime(boost::posix_time::microsec_clock::local_time(),
                                                 boost::local_time::time_zone_ptr());
  auto facet = new boost::posix_time::time_facet("%Y %m %d %H %M %s");
  ss.imbue(std::locale(std::locale::classic(), facet));
  ss << currentTime.local_time();

  return ss.str();
}

// generating local time to string without facet
string ConfigParam::GenLocalTimeStringNormal()
{
  std::stringstream ss;
  boost::local_time::local_date_time currentTime(boost::posix_time::second_clock::local_time(),
                                                 boost::local_time::time_zone_ptr());
  ss << currentTime.local_time();

  return ss.str();
}

void ConfigParam::ReadRosParam(ros::NodeHandle& nh, const string& key, float& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}

void ConfigParam::ReadRosParam(ros::NodeHandle& nh, const string& key, double& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}

void ConfigParam::ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}

void ConfigParam::ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
}

void ConfigParam::ReadRosParam(ros::NodeHandle& nh, const string& key, string& val)
{
  if (!nh.hasParam(key))
    throw RosParamNotFoundException(key);
  nh.getParam(key, val);
  if (val.empty())
    throw RosParamNotFoundException(key);
}

double ConfigParam::MapRange(double sourceNumber, double fromA, double fromB, double toA, double toB,
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

int ConfigParam::sat(int nVal, int nMin, int nMax)
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

float ConfigParam::sat(float fVal, float fMin, float fMax)
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

double ConfigParam::sat(double dVal, double dMin, double dMax)
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
