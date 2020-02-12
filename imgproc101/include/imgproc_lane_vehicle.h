// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>
#include <ros/package.h>
#include <opencv2/opencv.hpp>

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

class ImgProc101
{
public:
  ImgProc101();
  ~ImgProc101();

  void MainLoop();  

private:

  void LaneDetection(unsigned char *RGBimg, int height, int width);
  void VehicleDetection(unsigned char *RGBimg, int height, int width);

  bool ReadRosParams();
  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);  

  string strPkgEnv_;
  string strImgFolder_;
  string strLaneImgFile_;
  string strVehicleImgFile_;

  IplImage *LDimg_, *VDimg_;
};