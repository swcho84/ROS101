#ifndef JOYSTICK_101_GLOBAL_HEADER_H
#define JOYSTICK_101_GLOBAL_HEADER_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <random>
#include <chrono>
#include <cstdio>

// for using boost asio library
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/filesystem.hpp>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// for using image processing
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CompressedImage.h>

// for using simulate keyboard
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#ifdef Success
#undef Success
#endif

// for using eigen library
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

// for using tf w.r.t the quaternion
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/utils.h>

// for using joystick
#include <std_msgs/UInt8.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Joy.h>

// for using trajectory_msgs/MultiDOFJointTrajectory msg
#include <trajectory_msgs/MultiDOFJointTrajectory.h>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <geometry_msgs/Transform.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <mav_msgs/conversions.h>
#include <mav_msgs/default_topics.h>

// for using morai simulator, external joystick control (using xbox360)
#include "morai_msgs/CtrlCmd.h"
#include "morai_msgs/MultiEgoSetting.h"
#include "morai_msgs/EgoVehicleStatus.h"
#include "morai_msgs/ObjectStatusList.h"
#include "morai_msgs/ObjectStatus.h"
#include "morai_msgs/MoraiEventCmdSrv.h"
#include "morai_msgs/EventInfo.h"

// for using xplane11 simulator, external joystick control (using logitech extream)
#include "joystick_101/XPlaneJoyCtrlCmd.h"

// for using viewlink gimbal test, external joystick control (using xbox360)
#include "joystick_101/ViewLinkJoyCtrlCmd.h"

using namespace std;
using namespace ros;
using namespace cv;

#define PI 3.141592
#define R2D 180.0 / PI
#define D2R PI / 180.0
#define MPS2KMPH 3600.0 / 1000.0
#define CTRLGEAR 2
#define PGEAR 1
#define RGEAR 2
#define DGEAR 4
#define NEARDIST 4.0
#define MIDDIST 7.5
#define FARDIST 11.0
#define FORCEDSHUTTER 10.0
#define ROTORSHEADLESSCTRL 1
#define ROTORSHEADINGCTRL 2

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
  int nTrigShoot;
  int nTrigIrImgMode;
  int nTrigAllImgMode;
  int nTrigStabMode;
  int nTrigPosMode;
  int nTrigVelMode;
} CtrlButton;

typedef struct
{
  float fAttPhi;
  float fAttTheta;
  float fAttRatePsi;
  float fVelHeave;
  float fPhiAuxAccumScale;
  float fThetaAuxAccumScale;
  float fPhiAuxAccumMax;
  float fThetaAuxAccumMax;
  float fPsiAuxMin;
  float fPsiAuxMax;
  int nPsiResol;
  float fThrAuxMin;
  float fThrAuxMax;
  int nThrResol;
} CtrlRefScale;

typedef struct
{
  float fFwdVel;
  float fSteer;
} MoraiScale;

typedef struct
{
  float fHeightAccum;
  float fYawAng;
} RotorSscale;

typedef struct
{
  CtrlAxis ctrlMove;
  CtrlAuxilAxis ctrlAuxMove;
  CtrlButton ctrlButton;
  CtrlRefScale ctrlScale;
} JoyRaw;

typedef struct
{
  CtrlAxis ctrlMove;
  CtrlAuxilAxis ctrlAuxMove;
  CtrlRefScale ctrlScale;
  bool bCtrlAutoMode;
  bool bCtrlJoyMode;
  int nRgearStatus;
  int nDgearStatus;
  int nShootStatus;
  int nIrImgModeStatus;
  int nAllImgModeStatus;
  int nStabModeStatus;
  int nPosModeStatus;
  int nVelModeStatus;
} JoyCtrlCmd;

typedef struct
{
  double dPosXNed;
  double dPosYNed;
  double dPosZNed;
  double dHeadAng;
  Mat imgSrc;
} MoraiVehicleStatus;

typedef struct
{
  string strObjName;
  double dRelXNed;
  double dRelYNed;
  double dRelZNed;
  double dRelHead;
  double dRelEuDist;
} RelObjStatus;

#endif  // JOYSTICK_101_GLOBAL_HEADER_H
