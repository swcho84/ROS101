#include "joy_xplane_ctrl_lib.h"

using namespace std;
using namespace ros;

JoyXPlaneCtrl::JoyXPlaneCtrl(const ConfigParam& cfg) : cfgParam_(cfg), joyLogiExtream_(cfg)
{
  // generating publisher, vehicle control command joystick_101::XPlaneJoyCtrlCmd
  ROS_INFO("Publisher(xplane11_simulator_joystick_control_command): %s", cfgParam_.strXPlaneJoyCtrlTpNm.c_str());
  pubXPlaneJoySimCtrlCmd_ = nh_.advertise<joystick_101::XPlaneJoyCtrlCmd>(cfgParam_.strXPlaneJoyCtrlTpNm, 1);
}

JoyXPlaneCtrl::~JoyXPlaneCtrl()
{
}

// main loop
void JoyXPlaneCtrl::MainLoop()
{
  // generating the joystick command
  joyXPlaneJoySimCtrlCmd_ = joyLogiExtream_.GenJoyInfoLoop();

  // publishing the joystick control command for the xplane11 simulator
  joystick_101::XPlaneJoyCtrlCmd msgPubXplaneSimCtrlCmd;
  msgPubXplaneSimCtrlCmd.rollaxis =
      (float)((joyXPlaneJoySimCtrlCmd_.ctrlScale.fAttPhi) * (joyXPlaneJoySimCtrlCmd_.ctrlMove.fRoll));
  msgPubXplaneSimCtrlCmd.pitchaxis =
      (float)((joyXPlaneJoySimCtrlCmd_.ctrlScale.fAttTheta) * (joyXPlaneJoySimCtrlCmd_.ctrlMove.fPitch));
  msgPubXplaneSimCtrlCmd.yawaxis = (float)((cfgParam_.fAttPsi) * (joyXPlaneJoySimCtrlCmd_.ctrlMove.fYaw));
  msgPubXplaneSimCtrlCmd.throttleaxis = (float)(joyXPlaneJoySimCtrlCmd_.ctrlMove.fThr);
  msgPubXplaneSimCtrlCmd.flapaxis = (float)(joyXPlaneJoySimCtrlCmd_.ctrlAuxMove.fPitch);
  msgPubXplaneSimCtrlCmd.tvcaxis = (float)(joyXPlaneJoySimCtrlCmd_.ctrlAuxMove.fRoll);
  msgPubXplaneSimCtrlCmd.automode = (float)(joyXPlaneJoySimCtrlCmd_.bCtrlAutoMode);
  msgPubXplaneSimCtrlCmd.joymode = (float)(joyXPlaneJoySimCtrlCmd_.bCtrlJoyMode);
  pubXPlaneJoySimCtrlCmd_.publish(msgPubXplaneSimCtrlCmd);
  return;
}
