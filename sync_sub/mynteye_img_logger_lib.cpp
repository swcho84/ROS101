#include "mynteye_img_logger_lib.h"

using namespace std;
using namespace ros;
using namespace cv;
using namespace message_filters;

MyntEyeImgLogger::MyntEyeImgLogger(const ConfigParam& cfg)
  : cfgParam_(cfg), it_(nh_), nHeight_(640), nWidth_(480), bStartCamCallBack_(false), dAccumTime_(0.0)
{
  // generating log folder
  GenLogFolder(cfgParam_.strCamImgLogFolderPath);

  // generating callback function using synced subscriber
  subColorLeftImg_.reset(
      new message_filters::Subscriber<sensor_msgs::Image>(nh_, cfgParam_.strSubTpNmMyntEyeImgLeftColor, 1));
  subDepthImg_.reset(
      new message_filters::Subscriber<sensor_msgs::Image>(nh_, cfgParam_.strSubTpNmMyntEyeImgDepthRaw, 1));
  subCamLeftInfo_.reset(
      new message_filters::Subscriber<sensor_msgs::CameraInfo>(nh_, cfgParam_.strSubTpNmMyntEyeCamInfo, 1));
  subImuData_.reset(new message_filters::Subscriber<sensor_msgs::Imu>(nh_, cfgParam_.strSubTpNmMyntEyeImuDataProc, 1));
  sync_.reset(new Sync(mySyncPolicy(10), *subColorLeftImg_, *subDepthImg_, *subCamLeftInfo_, *subImuData_));
  sync_->registerCallback(boost::bind(&MyntEyeImgLogger::CbSyncData, this, _1, _2, _3, _4));
}

MyntEyeImgLogger::~MyntEyeImgLogger()
{
}

// callback function using synced data for mynteye camera
void MyntEyeImgLogger::CbSyncData(const sensor_msgs::ImageConstPtr& msgImgColor,
                                  const sensor_msgs::ImageConstPtr& msgImgDepth,
                                  const sensor_msgs::CameraInfoConstPtr& msgCamInfo,
                                  const sensor_msgs::ImuConstPtr& msgImuData)
{
  // grabbing the image frame, color image
  try
  {
    cvPtrImgColorSrc_ = cv_bridge::toCvCopy(msgImgColor, sensor_msgs::image_encodings::BGR8);
    bStartCamCallBack_ = true;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("CamImgLogger::cv_bridge, color, exception: %s", e.what());
    bStartCamCallBack_ = false;
    return;
  }

  // grabbing the image frame, depth image
  try
  {
    cvPtrImgDepthSrc_ = cv_bridge::toCvCopy(msgImgDepth, sensor_msgs::image_encodings::TYPE_16UC1);
    bStartCamCallBack_ = true;
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("CamImgLogger::cv_bridge, depth exception: %s", e.what());
    bStartCamCallBack_ = false;
    return;
  }

  // making raw and depth image
  Mat& imgColorRaw = cvPtrImgColorSrc_->image;
  Mat& imgDepthRaw = cvPtrImgDepthSrc_->image;
  imgColorRaw.copyTo(imgColorRaw_);
  imgDepthRaw.copyTo(imgDepthRaw_);

  // image width and height info. (h1024, w2048)
  nHeight_ = imgColorRaw.rows;
  nWidth_ = imgColorRaw.cols;

  // generating processed depth image
  imgDepthNorm_ = GenNormDepthImg(imgDepthRaw);
  imgDepthFalseColor_ = GenFalseColorDepthImg(imgDepthNorm_);

  // generating camera intrinsic, extrinsic information
  camInfoRaw_ = *msgCamInfo;

  // generating inertial info w.r.t. body axis
  bodyInertialInfo_ = GenImuData(msgImuData);
}

// main loop
void MyntEyeImgLogger::MainLoop(double dt)
{
  // executing this loop only bStartCamCallBack_ is true
  if (!bStartCamCallBack_)
    return;

  // saving image in the target folder
  SaveRawImg(dt, imgColorRaw_, cfgParam_.strCamImgLogFolderPath);

  // for highgui window
  waitKey(5);
  return;
}

// saving image in the target folder
bool MyntEyeImgLogger::SaveRawImg(double dt, Mat imgInput, string strFolderPath)
{
  bool bRes = false;
  string strFilePath;

  // making time accumulator and file name
  dAccumTime_ += dt;
  strFilePath = strFolderPath + "/" + "etridb_ca_raw_" + cfgParam_.GenLocalTimeStringNormal() + "." +
                cfgParam_.strCamImgLogFileType;

  // saving loop
  if (dAccumTime_ > cfgParam_.dCamImgLogHz)
  {
    imwrite(strFilePath, imgInput);
    dAccumTime_ = 0.0;
  }

  return bRes;
}

// generating log folder
bool MyntEyeImgLogger::GenLogFolder(string strFolderPath)
{
  // default: -1, folder generation failure status
  // 0, folder generation success
  ROS_INFO("Log folder path: %s", strFolderPath.c_str());
  boost::filesystem::path dataDir(strFolderPath.c_str());

  int nRes = -1;
  if (!boost::filesystem::is_directory(dataDir))
  {
    ROS_INFO("Making log folder in ~/.ros folder, %s", strFolderPath.c_str());

    // 0777: full permission for access, read and write
    nRes = mkdir(strFolderPath.c_str(), 0777);
  }
  else
  {
    ROS_INFO("Log folder path is exist..");
    nRes = 0;
  }

  // generating folder status
  if (nRes == 0)
  {
    ROS_INFO("Success: log folder generation, path: %s", strFolderPath.c_str());
    return true;
  }
  else if (nRes < 0)
  {
    ROS_ERROR("Failure: log folder generation, path: %s", strFolderPath.c_str());
    return false;
  }
  else
  {
    ROS_ERROR("Error: log folder generation, path: %s", strFolderPath.c_str());
    return false;
  }
}

// making imu data
BodyLinAccRotRate MyntEyeImgLogger::GenImuData(const sensor_msgs::ImuConstPtr& msgImuData)
{
  sensor_msgs::Imu imuRaw;
  imuRaw = *msgImuData;

  BodyLinAccRotRate res;
  res.linAcc(0) = imuRaw.linear_acceleration.x;
  res.linAcc(1) = imuRaw.linear_acceleration.y;
  res.linAcc(2) = imuRaw.linear_acceleration.z;
  res.rotRate(0) = imuRaw.angular_velocity.x;
  res.rotRate(1) = imuRaw.angular_velocity.y;
  res.rotRate(2) = imuRaw.angular_velocity.z;

  return res;
}

// making normalized depth image
Mat MyntEyeImgLogger::GenNormDepthImg(Mat imgInput)
{
  double min;
  double max;
  minMaxIdx(imgInput, &min, &max);
  float scale = 255 / (max - min);

  // Histogram Equalization
  Mat imgRes;
  imgInput.convertTo(imgRes, CV_8UC1, scale, -min * scale);

  return imgRes;
}

// making color-based depth image
Mat MyntEyeImgLogger::GenFalseColorDepthImg(Mat imgInput)
{
  // this is great. It converts your grayscale image into a tone-mapped one,
  // much more pleasing for the eye
  // function is found in contrib module, so include contrib.hpp
  // and link accordingly
  Mat imgRes;
  applyColorMap(imgInput, imgRes, COLORMAP_RAINBOW);
  return imgRes;
}