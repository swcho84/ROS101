// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// for using standard messages
#include <std_msgs/Float32MultiArray.h>

// for using custom define enum variable
#include <custom_msg_srv_param_ros/Define.h>

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

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

class PubSinusoidalSignalNode
{
public:
  PubSinusoidalSignalNode();
  ~PubSinusoidalSignalNode();

  void MainLoop();

private:
  void PubSinusoidalSignal();

  bool ReadRosParams();
  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);
  
  // node handler in class
  NodeHandle nh_;

  int nSize_;
  float fSigA_;
  float fSigB_;
  float fSigC_;

  // publisher, three signal, float32 multi-array
  string strTpNameSigInfo_;
  Publisher pubSignalArray_;
  std_msgs::Float32MultiArray msgSignalArray_;
};