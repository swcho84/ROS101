#include "joy_morai_ctrl_lib.h"

using namespace std;
using namespace ros;

JoyMoraiCtrl::JoyMoraiCtrl(const ConfigParam& cfg) : cfgParam_(cfg), joyXbox360_(cfg), moraiAutoLog_(cfg), it_(nh_)
{
  // generating publisher, vehicle control command
  ROS_INFO("Publisher(morai_simulator_control_command): %s", cfgParam_.strMoraiSimJoyCtrlTpNm.c_str());
  pubMoraiSimCtrlCmd_ = nh_.advertise<morai_msgs::CtrlCmd>(cfgParam_.strMoraiSimJoyCtrlTpNm, 1);

  // generating publisher, vehicle gear command
  ROS_INFO("Publisher(morai_simulator_gear_command): %s", cfgParam_.strMoraiSimPoseCtrlTpNm.c_str());
  pubMoraiSimPoseCmd_ = nh_.advertise<morai_msgs::MultiEgoSetting>(cfgParam_.strMoraiSimPoseCtrlTpNm, 1);

  // generating subscriber, vehicle status
  ROS_INFO("Subscriber(morai_simulator_vehicle_status): %s", cfgParam_.strMoraiSimVehicleStatusTpNm.c_str());
  subMoraiSimVehicleStatus_ = nh_.subscribe<morai_msgs::EgoVehicleStatus>(cfgParam_.strMoraiSimVehicleStatusTpNm, 1,
                                                                          &JoyMoraiCtrl::CbMoraiVehicleStatus, this);

  // generating subscriber, object status
  ROS_INFO("Subscriber(morai_simulator_object_status): %s", cfgParam_.strMoraiObjectStatusTpNm.c_str());
  subMoraiObjectStatus_ = nh_.subscribe<morai_msgs::ObjectStatusList>(cfgParam_.strMoraiObjectStatusTpNm, 1,
                                                                      &JoyMoraiCtrl::CbMoraiObjectStatus, this);

  // generating subscriber, raw image with compressed option
  image_transport::TransportHints compHint("compressed");
  ROS_INFO("Subscriber(morai_simulator_raw_img_status): %s", cfgParam_.strMoraiRawImgTpNm.c_str());
  subRawImg_ = it_.subscribe(cfgParam_.strMoraiRawImgTpNm, 1, &JoyMoraiCtrl::CbRawImgData, this, compHint);

  // generating subscriber, image data logger command
  ROS_INFO("Subscriber(morai_simulator_img_log_status): %s", cfgParam_.strMoraiImgLogCmdTpNm.c_str());
  subMoraiSimRosBagImgLog_ =
      nh_.subscribe<std_msgs::UInt8>(cfgParam_.strMoraiImgLogCmdTpNm, 1, &JoyMoraiCtrl::CbMoraiImgLogCmdtatus, this);

  // generating service client, setting reverse/drive gear
  srvClientSetGearInfo_ = nh_.serviceClient<morai_msgs::MoraiEventCmdSrv>(cfgParam_.strMoraiSetGearSrvNm);

  // initializing variables
  bEgoVehicleStatus_ = false;
  bStartImgCallBack_ = false;
  bEgoVehiclePoseCalStatus_ = false;
  bObjectStatusList_ = false;
  bImgLogStatus_ = false;

  // initializing display for virtual keyboard test
  disp_ = XOpenDisplay(NULL);
  dTimeCounter_ = 0.0;
  dTimeSaver_ = 0.0;
  fShutterCmd_ = 0.0f;
  nDbCurrLogSize_ = 0;
  nDbTotalLogSize_ = 0;
}

JoyMoraiCtrl::~JoyMoraiCtrl()
{
}

// callback function, morai sim imglog command status
void JoyMoraiCtrl::CbMoraiImgLogCmdtatus(const std_msgs::UInt8::ConstPtr& msgRaw)
{
  // 1: start imglog, 0: stop imglog
  msgImgLogCmd_ = *msgRaw;
}

// callback function, morai vehicle status
void JoyMoraiCtrl::CbMoraiVehicleStatus(const morai_msgs::EgoVehicleStatus::ConstPtr& msgRaw)
{
  msgEgoVehicleStatus_ = *msgRaw;
  bEgoVehicleStatus_ = true;
}

// callback function, morai object status
void JoyMoraiCtrl::CbMoraiObjectStatus(const morai_msgs::ObjectStatusList::ConstPtr& msgRaw)
{
  msgObjectStatusList_ = *msgRaw;
  bObjectStatusList_ = true;
}

// callback function using synced data for mynteye camera
void JoyMoraiCtrl::CbRawImgData(const sensor_msgs::ImageConstPtr& msgRaw)
{
  // grabbing the image frame, color image
  try
  {
    cvPtrImgSrc_ = cv_bridge::toCvCopy(msgRaw, sensor_msgs::image_encodings::BGR8);
    bStartImgCallBack_ = true;
    resize(cvPtrImgSrc_->image, imgSrc_, cfgParam_.sizeVgaRaw);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR_DELAYED_THROTTLE(10, "CamImgLogger::cv_bridge, color, exception: %s", e.what());
    bStartImgCallBack_ = false;
    return;
  }
}

// main loop
void JoyMoraiCtrl::MainLoop(double dt)
{
  // generating the joystick command
  joyMoraiSimCtrlCmd_ = joyXbox360_.GenJoyInfoLoop();

  // making the shutter command using yawRt trigger
  fShutterCmd_ = joyMoraiSimCtrlCmd_.ctrlAuxMove.fYawRt;
  GenShutterJoyCmd(fShutterCmd_, dt);

  // making the gear command
  morai_msgs::MoraiEventCmdSrv srvClientSetGear;
  morai_msgs::EventInfo msgEventInfo;
  msgEventInfo.option = CTRLGEAR;  // setting gear control
  if ((joyMoraiSimCtrlCmd_.nRgearStatus == 1) && (joyMoraiSimCtrlCmd_.nDgearStatus == 0))
  {
    msgEventInfo.gear = RGEAR;  // R, reverse gear
    ROS_INFO_DELAYED_THROTTLE(10, "reverse gear activate...");
  }
  else if ((joyMoraiSimCtrlCmd_.nRgearStatus == 0) && (joyMoraiSimCtrlCmd_.nDgearStatus == 1))
  {
    msgEventInfo.gear = DGEAR;  // D, drive gear
    ROS_INFO_DELAYED_THROTTLE(10, "drive gear activate...");
  }
  else
  {
    msgEventInfo.gear = DGEAR;  // D, drive gear
  }
  srvClientSetGear.request.request = msgEventInfo;
  srvClientSetGearInfo_.call(srvClientSetGear);

  // publishing the joystick control command for the morai simulator
  morai_msgs::CtrlCmd msgPubMoraiSimCtrlCmd;
  msgPubMoraiSimCtrlCmd.longlCmdType = 2;
  msgPubMoraiSimCtrlCmd.velocity = (cfgParam_.moraiSimCtrlScale.fFwdVel) * (joyMoraiSimCtrlCmd_.ctrlMove.fThr);
  msgPubMoraiSimCtrlCmd.steering = (-1.0f) * (cfgParam_.moraiSimCtrlScale.fSteer) * (joyMoraiSimCtrlCmd_.ctrlMove.fYaw);
  pubMoraiSimCtrlCmd_.publish(msgPubMoraiSimCtrlCmd);

  // using rosbag-based imglog mode
  if ((bool)(msgImgLogCmd_.data))
  {
    // logging imgdb data, usleep(in micro second, 10^-6)
    usleep(cfgParam_.nLogDuration);
    GenShutterAutoCmd();
    ROS_INFO("MoraiImgDBlogSize(curr,total):(%d,%d)", nDbCurrLogSize_, nDbTotalLogSize_);
    usleep(cfgParam_.nLogDuration);
    nDbCurrLogSize_++;
    nDbTotalLogSize_ += nDbCurrLogSize_;
  }
  else
    nDbCurrLogSize_ = 0;

  // // using auto imglog mode, pose set generation
  // vector<morai_msgs::MultiEgoSetting> vecVehiclePose;
  // if ((joyMoraiSimCtrlCmd_.bCtrlAutoMode) && (!bEgoVehiclePoseCalStatus_))
  // {
  //   // making vehicle state with the tagged image
  //   MoraiVehicleStatus vehicleStatus;
  //   vehicleStatus.dPosXNed = msgEgoVehicleStatus_.position.x;
  //   vehicleStatus.dPosYNed = msgEgoVehicleStatus_.position.y;
  //   vehicleStatus.dPosZNed = msgEgoVehicleStatus_.position.z;
  //   vehicleStatus.dHeadAng = (msgEgoVehicleStatus_.heading);
  //   imgSrc_.copyTo(vehicleStatus.imgSrc);

  //   // generating a set of vehicle pose status
  //   vecVehiclePose = moraiAutoLog_.ImgLogLoop(dt, vehicleStatus, msgObjectStatusList_);

  //   // continuous mode(false), one-shot mode(true)
  //   bEgoVehiclePoseCalStatus_ = false;
  // }

  // // replaying the pose set and saving the image data
  // if ((vecVehiclePose.size() > 0) && (!bImgLogStatus_))
  // {
  //   for (auto i = 0; i < vecVehiclePose.size(); i++)
  //   {
  //     // publishing the single ego vehicle pose
  //     pubMoraiSimPoseCmd_.publish(vecVehiclePose[i]);
  //     usleep(500000);
  //     GenShutterAutoCmd();
  //     usleep(500000);

  //     if ((i + 1) == vecVehiclePose.size())
  //       break;
  //     else
  //       ROS_INFO("(i,size):(%d,%d)", (int)(i), (int)(vecVehiclePose.size()));
  //   }

  //   // continuous mode(false), one-shot mode(true)
  //   bImgLogStatus_ = true;
  // }

  // // resetting the pose set
  // if ((joyMoraiSimCtrlCmd_.bCtrlJoyMode) && (bEgoVehiclePoseCalStatus_))
  // {
  //   bEgoVehiclePoseCalStatus_ = false;
  //   bImgLogStatus_ = false;
  // }

  return;
}

// generating the shutter command, using automatic command
void JoyMoraiCtrl::GenShutterAutoCmd()
{
  SendKey(disp_, XK_space, 0);
  ROS_INFO("GenShutterAutoCmd::MoraiSim..");
  return;
}

// generating the shutter command, using joystick
void JoyMoraiCtrl::GenShutterJoyCmd(float shutter, double dt)
{
  dTimeCounter_ += dt;
  if ((shutter > 0.5f) && (dTimeCounter_ > 1.0))
  {
    SendKey(disp_, XK_space, 0);
    ROS_INFO("GenShutterJoyCmd::MoraiSim..");
    dTimeCounter_ = 0.0;
  }
  return;
}

// sending the fake keyboard event, for generating shutter command (assumption: activated window is Morai simulator)
void JoyMoraiCtrl::SendKey(Display* disp, KeySym keysym, KeySym modsym)
{
  KeyCode keycode = 0, modcode = 0;
  keycode = XKeysymToKeycode(disp, keysym);
  if (keycode == 0)
    return;

  XTestGrabControl(disp, True);

  // generating modkey press
  if (modsym != 0)
  {
    modcode = XKeysymToKeycode(disp, modsym);
    XTestFakeKeyEvent(disp, modcode, True, 0);
  }

  // generating the regular key press and release
  XTestFakeKeyEvent(disp, keycode, True, 0);
  XTestFakeKeyEvent(disp, keycode, False, 0);

  // generating the modkey release
  if (modsym != 0)
    XTestFakeKeyEvent(disp, modcode, False, 0);

  XSync(disp, False);
  XTestGrabControl(disp, False);
  return;
}
