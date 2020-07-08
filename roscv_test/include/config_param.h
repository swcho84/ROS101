#ifndef ROSCV_TEST_CONFIG_PARAM_H
#define ROSCV_TEST_CONFIG_PARAM_H

#include "global_header.h"

using namespace std;
using namespace ros;

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

  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);

  string strHomeName;
  string strPicType;
  string strPolygonType;
  string strXmlType;
  string strRawFolderNm;
  string strRawFolderPath;
  string strAnnoFolderNm;
  string strAnnoFolderPath;
  string strPolygonFolderNm;
  string strPolygonFolderPath;
  string strXmlFolderNm;
  string strXmlFolderPath;

  int nCannyThresh;
  int nMorphThresh;
  int nPolyDPThesh;

  vector<string> vecLabels;
  vector<AnnoDB> vecAnnoDB;
  
  vector<vector<BboxDB>> vecImgBboxDB;
  vector<vector<BboxDB>> vecPolygonBboxDB;  

  AnnoDB vegetation;
  AnnoDB person;
  AnnoDB rider;
  AnnoDB car;
  AnnoDB truck;
  AnnoDB bus;
  AnnoDB caravan;
  AnnoDB trailer;
  AnnoDB motorcycle;
  AnnoDB bicycle;


private:
  bool ReadRosParams();

};

#endif  // ROSCV_TEST_CONFIG_PARAM_H