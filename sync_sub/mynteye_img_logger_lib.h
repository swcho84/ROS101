#ifndef CAMIMG_LOGGER_CAMIMG_LOGGER_LIB_H
#define CAMIMG_LOGGER_CAMIMG_LOGGER_LIB_H

#include "global_header.h"
#include "config_param.h"

using namespace std;
using namespace ros;
using namespace cv;

class MyntEyeImgLogger
{
public:
  MyntEyeImgLogger(const ConfigParam& cfg);
  ~MyntEyeImgLogger();

  void MainLoop(double dt);

private:
  ConfigParam cfgParam_;
  BodyLinAccRotRate bodyInertialInfo_;

  sensor_msgs::CameraInfo camInfoRaw_;

  bool GenLogFolder(string strFolderPath);
  bool SaveRawImg(double dt, Mat imgInput, string strFolderPath);

  Mat GenFalseColorDepthImg(Mat imgInput);
  Mat GenNormDepthImg(Mat imgInput);
  BodyLinAccRotRate GenImuData(const sensor_msgs::ImuConstPtr& msgImuData);

  void CbSyncData(const sensor_msgs::ImageConstPtr& msgImgColor, const sensor_msgs::ImageConstPtr& msgImgDepth,
                  const sensor_msgs::CameraInfoConstPtr& msgCamInfo, const sensor_msgs::ImuConstPtr& msgImuData);

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;

  // ROS message for images
  cv_bridge::CvImagePtr cvPtrImgSrc_;
  cv_bridge::CvImagePtr cvPtrImgColorSrc_;
  cv_bridge::CvImagePtr cvPtrImgDepthSrc_;

  // synced subscriber
  std::unique_ptr<message_filters::Subscriber<sensor_msgs::Image> > subColorLeftImg_;
  std::unique_ptr<message_filters::Subscriber<sensor_msgs::Image> > subDepthImg_;
  std::unique_ptr<message_filters::Subscriber<sensor_msgs::CameraInfo> > subCamLeftInfo_;
  std::unique_ptr<message_filters::Subscriber<sensor_msgs::Imu> > subImuData_;
  typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image,
                                                          sensor_msgs::CameraInfo, sensor_msgs::Imu>
      mySyncPolicy;
  typedef message_filters::Synchronizer<mySyncPolicy> Sync;
  std::shared_ptr<Sync> sync_;

  int nHeight_;
  int nWidth_;

  bool bStartCamCallBack_;

  double dAccumTime_;

  Mat imgColorRaw_;
  Mat imgDepthRaw_;
  Mat imgDepthNorm_;
  Mat imgDepthFalseColor_;
};

#endif