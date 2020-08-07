#ifndef CAMIMG_LOGGER_CONFIG_PARAM_H
#define CAMIMG_LOGGER_CONFIG_PARAM_H

#include "global_header.h"
#include "var_struct.h"

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
  TimeDB GenLocalTimeVec(string strTime);
  string GenLocalTimeStringNormal();
  string GenLocalTimeStringFacet();

  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);

  ros::Time rosCurrTime;
  ros::Time rosLastTime;
  double dt;

  string strHomeName;

  string strSubTpNmMyntEyeCamInfo;
  string strSubTpNmMyntEyeImgLeftColor;
  string strSubTpNmMyntEyeImgDepthRaw;
  string strSubTpNmMyntEyeImuDataProc;
  string strPubTpNmMyntEyeImgImuSync;

  string strCamImgLogFileType;
  string strCamImgLogFolderNm;
  string strCamImgLogFolderPath;

  int nCamImgLogCase;

  double dCamImgLogHz;

private:
  bool ReadRosParams();
};

#endif  // ROSCV_TEST_CONFIG_PARAM_H