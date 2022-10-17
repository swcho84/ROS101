#include "joy_viewlink_ctrl_lib.h"

using namespace std;
using namespace ros;

JoyViewLinkCtrl::JoyViewLinkCtrl(const ConfigParam& cfg) : cfgParam_(cfg), joyXbox360_(cfg), joyLogiExtream_(cfg)
{
  // generating publisher, viewlink gimbal control command joystick_101::ViewLinkJoyCtrlCmd
  ROS_INFO("Publisher(viewlink_gimbal_joystick_control_command): %s", cfgParam_.strViewLinkJoyCtrlTpNm.c_str());
  pubViewLinkJoyCtrlCmd_ = nh_.advertise<joystick_101::ViewLinkJoyCtrlCmd>(cfgParam_.strViewLinkJoyCtrlTpNm, 1);
}

JoyViewLinkCtrl::~JoyViewLinkCtrl()
{
}

// main loop
void JoyViewLinkCtrl::MainLoop()
{
  if (cfgParam_.strViewLinkJoySelect == "xbox")
  {
    // generating the joystick command
    joyViewLinkCtrlCmd_ = joyXbox360_.GenJoyInfoLoop();
  }
  else if (cfgParam_.strViewLinkJoySelect == "logitech")
  {
    // generating the joystick command
    joyViewLinkCtrlCmd_ = joyLogiExtream_.GenJoyInfoLoop();
  }
  else
    ROS_ERROR_DELAYED_THROTTLE(10, "please check the joystick connection status..");

  // for debugging
  // ROS_INFO("rpy:(%.4lf,%.4lf,%.4lf)", joyViewLinkCtrlCmd_.ctrlMove.fRoll, joyViewLinkCtrlCmd_.ctrlMove.fPitch,
  //          joyViewLinkCtrlCmd_.ctrlMove.fYaw);
  // ROS_INFO("thr:(%.4lf)", joyViewLinkCtrlCmd_.ctrlMove.fThr);
  // ROS_INFO("rp_accum:(%.4lf,%.4lf)", joyViewLinkCtrlCmd_.ctrlAuxMove.fRoll, joyViewLinkCtrlCmd_.ctrlAuxMove.fPitch);
  // ROS_INFO("autojoy:(%d,%d)", (int)(joyViewLinkCtrlCmd_.bCtrlAutoMode), (int)(joyViewLinkCtrlCmd_.bCtrlJoyMode));
  // ROS_INFO("rd_gear:(%d,%d)", joyViewLinkCtrlCmd_.nRgearStatus, joyViewLinkCtrlCmd_.nDgearStatus);
  // ROS_INFO(" ");

  // publishing the joystick control command for the viewlink gimbal
  joystick_101::ViewLinkJoyCtrlCmd msgViewLinkJoyCtrlCmd;
  msgViewLinkJoyCtrlCmd.pan_rate_axis = (cfgParam_.dGimbalPanRateScale) * (joyViewLinkCtrlCmd_.ctrlMove.fRoll);
  msgViewLinkJoyCtrlCmd.tilt_rate_axis = (cfgParam_.dGimbalTiltRateScale) * (joyViewLinkCtrlCmd_.ctrlMove.fPitch);
  msgViewLinkJoyCtrlCmd.pan_ang_axis = (cfgParam_.dGimbalPanAngScale) * (joyViewLinkCtrlCmd_.ctrlAuxMove.fRoll);
  msgViewLinkJoyCtrlCmd.tilt_ang_axis =
      (-1.0) * (cfgParam_.dGimbalTiltAngScale) * (joyViewLinkCtrlCmd_.ctrlAuxMove.fPitch);
  msgViewLinkJoyCtrlCmd.zoom_axis =
      cfgParam_.MapRange(joyViewLinkCtrlCmd_.ctrlMove.fThr, 0.0, 1.0, 1.0, 30.0, 1.0);
  msgViewLinkJoyCtrlCmd.auto_mode = (double)(joyViewLinkCtrlCmd_.bCtrlAutoMode);
  msgViewLinkJoyCtrlCmd.manual_mode = (double)(joyViewLinkCtrlCmd_.bCtrlJoyMode);
  msgViewLinkJoyCtrlCmd.homing = (double)(joyViewLinkCtrlCmd_.nDgearStatus);
  msgViewLinkJoyCtrlCmd.shoot = (double)(joyViewLinkCtrlCmd_.nShootStatus);
  msgViewLinkJoyCtrlCmd.eo_img_submode = (double)(joyViewLinkCtrlCmd_.nRgearStatus);
  msgViewLinkJoyCtrlCmd.ir_img_submode = (double)(joyViewLinkCtrlCmd_.nIrImgModeStatus);
  msgViewLinkJoyCtrlCmd.all_img_submode = (double)(joyViewLinkCtrlCmd_.nAllImgModeStatus);
  msgViewLinkJoyCtrlCmd.stab_submode = (double)(joyViewLinkCtrlCmd_.nStabModeStatus);
  msgViewLinkJoyCtrlCmd.ang_ctrl_submode = (double)(joyViewLinkCtrlCmd_.nPosModeStatus);
  msgViewLinkJoyCtrlCmd.angrate_ctrl_submode = (double)(joyViewLinkCtrlCmd_.nVelModeStatus);      
  pubViewLinkJoyCtrlCmd_.publish(msgViewLinkJoyCtrlCmd);
  return;
}
