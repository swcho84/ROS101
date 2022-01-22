#include "joy_rotors_posctrl_lib.h"

using namespace std;
using namespace ros;
using namespace Eigen;

JoyRotorSPosCtrl::JoyRotorSPosCtrl(const ConfigParam& cfg) : cfgParam_(cfg), joyXbox360_(cfg), misc_(cfg)
{
  // generating publisher, rotors simulator position control command
  ROS_INFO("Publisher(rotors_simulator_joystick_control_command): %s", cfgParam_.strRotorsJoyPosCtrlTpNm.c_str());
  pubRotorSPosSimCtrlTrjCmd_ = nh_.advertise<geometry_msgs::PoseStamped>(cfgParam_.strRotorsJoyPosCtrlTpNm, 1);

  // generating subscriber, rotors simulator, pose information
  ROS_INFO("Subscriber(rotors_simulator_vehicle_pose): %s", cfgParam_.strRotorsPoseInfoTpNm.c_str());
  subPoseInfo_ = nh_.subscribe(cfgParam_.strRotorsPoseInfoTpNm, 1, &JoyRotorSPosCtrl::CbPoseInfo, this);

  // initializing commands
  dHeightRef_ = 0.0;
  dYawAngRef_ = 0.0;
  dHeadAngRef_ = 0.0;
  bYawInit_ = false;

  // initializing mav pose information
  for (unsigned int i = 0; i < 3; i++)
  {
    mavPosEnu_(i) = 0.0;
    mavPosNed_(i) = 0.0;
    mavEulerAtt_(i) = 0.0;
  }
}

JoyRotorSPosCtrl::~JoyRotorSPosCtrl()
{
}

// main loop
void JoyRotorSPosCtrl::MainLoop()
{
  // generating the joystick command, Mode 1
  joyRotorSPosSimCtrlCmd_ = joyXbox360_.GenJoyInfoLoop();

  // for debugging
  // RawJoyInfo();

  // selecting and calculating the position control command w.r.t the control and auto-engage mode
  geometry_msgs::PoseStamped msgPoseCtrlCmdInfo;
  msgPoseCtrlCmdInfo.header.stamp = ros::Time::now();
  switch (cfgParam_.nRotorSPosCtrlMode)
  {
    case ROTORSHEADLESSCTRL:
    {
      msgPoseCtrlCmdInfo = CalcPosCtrlHeadlessCmd(joyRotorSPosSimCtrlCmd_, autoRotorSPoseSimCtrlCmd_);
      break;
    }
    case ROTORSHEADINGCTRL:
    {
      msgPoseCtrlCmdInfo = CalcPosCtrlHeadingCmd(joyRotorSPosSimCtrlCmd_, autoRotorSPoseSimCtrlCmd_);
      break;
    }
  }

  // publishing the position control command
  pubRotorSPosSimCtrlTrjCmd_.publish(msgPoseCtrlCmdInfo);
  return;
}

// calculating the headless position control input, auto/joy
geometry_msgs::PoseStamped JoyRotorSPosCtrl::CalcPosCtrlHeadlessCmd(JoyCtrlCmd joyPosIn,
                                                                    geometry_msgs::PoseStamped autoPosIn)
{
  geometry_msgs::PoseStamped res;
  res.header.stamp = ros::Time::now();
  if (joyPosIn.bCtrlAutoMode)
  {
    // ENU frame (if you need to NED frame, please convert the position variable from NED to ENU)
    res.pose.position = autoPosIn.pose.position;
    res.pose.orientation = autoPosIn.pose.orientation;
  }
  else if (joyPosIn.bCtrlJoyMode)
  {
    // from NED frame to ENU frame
    Vector3d mavPosEnuTemp;
    dHeightRef_ += (cfgParam_.rotorScale.fHeightAccum) * (joyPosIn.ctrlMove.fThr);
    dYawAngRef_ = mavEulerAtt_(2) - ((cfgParam_.rotorScale.fYawAng) * (joyPosIn.ctrlMove.fYaw));
    mavPosEnuTemp =
        misc_.ConvertPosFromNedToEnu(CalcJoyPosCtrlCmdHeadless(joyPosIn, mavPosNed_, dHeightRef_, dYawAngRef_));
    res.pose.position.x = mavPosEnuTemp(0);
    res.pose.position.y = mavPosEnuTemp(1);
    res.pose.position.z = mavPosEnuTemp(2);

    // assigning yaw angle control using joystick, rotation
    Quaterniond rotQuat;
    rotQuat = misc_.CalcQuaternionFromYPREulerAng(CalcJoyYawCtrlCmd(dYawAngRef_));
    res.pose.orientation.x = rotQuat.x();
    res.pose.orientation.y = rotQuat.y();
    res.pose.orientation.z = rotQuat.z();
    res.pose.orientation.w = rotQuat.w();
  }
  else
    ROS_INFO_DELAYED_THROTTLE(10, "ROTORSHEADLESSCTRL::please check the auto/manual mode..");
  return res;
}

// calculating the heading position control input, auto/joy
geometry_msgs::PoseStamped JoyRotorSPosCtrl::CalcPosCtrlHeadingCmd(JoyCtrlCmd joyPosIn,
                                                                   geometry_msgs::PoseStamped autoPosIn)
{
  geometry_msgs::PoseStamped res;
  res.header.stamp = ros::Time::now();
  if (joyRotorSPosSimCtrlCmd_.bCtrlAutoMode)
  {
    // ENU frame (if you need to NED frame, please convert the position variable from NED to ENU)
    res.pose.position = autoPosIn.pose.position;
    res.pose.orientation = autoPosIn.pose.orientation;
  }
  else if (joyRotorSPosSimCtrlCmd_.bCtrlJoyMode)
  {
    // from NED frame to ENU frame, 0.0: current position (using position error model)
    Vector3d mavPosEnuTemp;
    Vector3d mavPosNedTemp;
    dHeightRef_ += (cfgParam_.rotorScale.fHeightAccum) * (joyPosIn.ctrlMove.fThr);
    dYawAngRef_ = mavEulerAtt_(2) - ((cfgParam_.rotorScale.fYawAng) * (joyPosIn.ctrlMove.fYaw));
    mavPosEnuTemp =
        misc_.ConvertPosFromNedToEnu(CalcJoyPosCtrlCmdHeading(joyPosIn, mavPosNed_, dHeightRef_, dYawAngRef_));
    res.pose.position.x = mavPosEnuTemp(0);
    res.pose.position.y = mavPosEnuTemp(1);
    res.pose.position.z = mavPosEnuTemp(2);

    // assigning yaw angle control using joystick, rotation
    Quaterniond rotQuat;
    rotQuat = misc_.CalcQuaternionFromYPREulerAng(CalcJoyYawCtrlCmd(dYawAngRef_));
    res.pose.orientation.x = rotQuat.x();
    res.pose.orientation.y = rotQuat.y();
    res.pose.orientation.z = rotQuat.z();
    res.pose.orientation.w = rotQuat.w();
  }
  else
    ROS_INFO_DELAYED_THROTTLE(10, "ROTORSHEADINGCTRL::please check the auto/manual mode..");
  return res;
}

// callback function, rotors pose information
void JoyRotorSPosCtrl::CbPoseInfo(const geometry_msgs::PoseConstPtr& msg)
{
  // converting enu data to ned data
  mavPosEnu_(0) = msg->position.x;
  mavPosEnu_(1) = msg->position.y;
  mavPosEnu_(2) = msg->position.z;
  mavPosNed_ = misc_.ConvertPosFromEnuToNed(mavPosEnu_);

  // for debugging
  // ROS_INFO("mavPosNed(n,e,d):(%.4f,%.4f,%.4f)", mavPosNed_(0), mavPosNed_(1), mavPosNed_(2));

  // attitude data, 3-2-1 Euler angle
  Quaterniond qAtt;
  Vector3d eulerAng;
  qAtt.x() = msg->orientation.x;
  qAtt.y() = msg->orientation.y;
  qAtt.z() = msg->orientation.z;
  qAtt.w() = msg->orientation.w;
  eulerAng = misc_.CalcYPREulerAngFromQuaternion(qAtt);
  mavEulerAtt_(0) = misc_.wrapD(eulerAng(0));
  mavEulerAtt_(1) = misc_.wrapD(eulerAng(1));
  mavEulerAtt_(2) = misc_.wrapD(eulerAng(2));

  // assigning the initial value
  if (!bYawInit_)
  {
    dHeadAngRef_ = mavEulerAtt_(2);
    bYawInit_ = true;
  }
}

// calculating the yaw control command using the joystick control input
Vector3d JoyRotorSPosCtrl::CalcJoyYawCtrlCmd(double dYawAngRef)
{
  Vector3d res;
  res(0) = mavEulerAtt_(0);
  res(1) = mavEulerAtt_(1);
  res(2) = misc_.wrapD(dYawAngRef_);
  return res;
}

// calculating the position control command using the joystick control input, only the headless mode
Vector3d JoyRotorSPosCtrl::CalcJoyPosCtrlCmdHeadless(JoyCtrlCmd joyPosIn, Vector3d posNedCurr, double dHeightRef,
                                                     double dYawAngRef)
{
  // negative pitch -> forward, positive pitch -> backward
  // negative roll -> leftside, positive roll -> rightside
  Vector3d res;
  res(0) = posNedCurr(0) - joyPosIn.ctrlMove.fPitch;
  res(1) = posNedCurr(1) + joyPosIn.ctrlMove.fRoll;
  res(2) = -dHeightRef;
  return res;
}

// calculating the position control command using the joystick control input, only the heading mode
Vector3d JoyRotorSPosCtrl::CalcJoyPosCtrlCmdHeading(JoyCtrlCmd joyPosIn, Vector3d posNedCurr, double dHeightRef,
                                                    double dYawAngRef)
{
  Vector3d res;
  Vector2d mavPosNed2DTemp;
  Vector2d mavPosNed2DCurr;
  Vector2d mavPosNed2DRef;
  mavPosNed2DCurr(0) = 0.0;
  mavPosNed2DCurr(1) = 0.0;
  mavPosNed2DRef(0) = joyPosIn.ctrlMove.fPitch;
  mavPosNed2DRef(1) = joyPosIn.ctrlMove.fRoll;
  mavPosNed2DTemp = misc_.Calc2DPosErrInfo(mavPosNed2DRef, mavPosNed2DCurr, dYawAngRef);
  res(0) = posNedCurr(0) - mavPosNed2DTemp(0);
  res(1) = posNedCurr(1) + mavPosNed2DTemp(1);
  res(2) = -dHeightRef;
  return res;
}

// for debugging, raw joystick data
void JoyRotorSPosCtrl::RawJoyInfo()
{
  ROS_INFO("axis(r%.4f,p%.4f,y%.4f,t%.4f)", joyRotorSPosSimCtrlCmd_.ctrlMove.fRoll,
           joyRotorSPosSimCtrlCmd_.ctrlMove.fPitch, joyRotorSPosSimCtrlCmd_.ctrlMove.fYaw,
           joyRotorSPosSimCtrlCmd_.ctrlMove.fThr);
  ROS_INFO("aux(r%.4f,p%.4f,ylt%.4f,yrt%.4f)", joyRotorSPosSimCtrlCmd_.ctrlAuxMove.fRoll,
           joyRotorSPosSimCtrlCmd_.ctrlAuxMove.fPitch, joyRotorSPosSimCtrlCmd_.ctrlAuxMove.fYawLt,
           joyRotorSPosSimCtrlCmd_.ctrlAuxMove.fYawRt);
  ROS_INFO("button(auto%d,joy%d)", (int)(joyRotorSPosSimCtrlCmd_.bCtrlAutoMode),
           (int)(joyRotorSPosSimCtrlCmd_.bCtrlJoyMode));
  ROS_INFO(" ");
}