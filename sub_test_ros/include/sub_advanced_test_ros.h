// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// for using custom messages
#include <custom_msg_srv_param_ros/RectArray.h>
#include <custom_msg_srv_param_ros/RectInfo.h>

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

class SubAdvancedTestNode
{
public:
  SubAdvancedTestNode();
  ~SubAdvancedTestNode();

  void MainLoop();

private:
  void SubAdvancedTestFunc();

  bool ReadRosParams();
  void ReadRosParam(ros::NodeHandle& nh, const string& key, float& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, double& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, bool& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, int32_t& val);
  void ReadRosParam(ros::NodeHandle& nh, const string& key, string& val);

  string strTpNameRectInfo_;

  // subscriber, custom msg
  void currRectArrayCbLoop(const RectArray::ConstPtr& msgRaw);
  Subscriber subRectArray_;
  RectArray msgRectArray_;
  vector<RectArray> vecRectArray_;
  bool bRectArraybLoop;
  
  // node handler in class
  NodeHandle nh_;
};