// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

using namespace std;
using namespace ros;

typedef struct
{
  float fA1;
  float fA2;
  float fA3;
} ParamSetA;

typedef struct
{
  double dB1;
  double dB2;
  double dB3;
} ParamSetB;

typedef struct
{
  int nC1;
  string strC2;
  bool bC3;
} ParamSetC;

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

class ReadParamTestNode
{
public:
  ReadParamTestNode();
  ~ReadParamTestNode();

  void MainLoop();

private:
  bool ReadRosParams();
  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);

  string strTpNameRectCounter_;
  string strTpNameRectInfo_;

  ParamSetA paramA_;
  ParamSetB paramB_;
  ParamSetC paramC_;
};