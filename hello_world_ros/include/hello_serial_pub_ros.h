// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <inttypes.h>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>
#include <ros/serialization.h>

// using serial library
#include <serial/serial.h>

// for using standard messages
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64MultiArray.h>

// for using custom mavlink
#include <mavlink_types.h>
#include <cju_swcho/mavlink.h>

// for using custom define enum variable
#include <custom_msg_srv_param_ros/Define.h>

#define MAV_SYS_ID 1
#define COMP_ID MAV_COMP_ID_FMCU

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

class HelloSerialPubRos
{
public:
  HelloSerialPubRos();
  ~HelloSerialPubRos();

  bool ConnectSerialPort();

  void MainLoop();  

private:

  // node handler in class
  NodeHandle nh_;

  void HelloFunction();

  void CbWriteToSerialTime(const std_msgs::Float64MultiArray::ConstPtr& msg);
  void CbWriteToSerialAtt(const std_msgs::Float32MultiArray::ConstPtr& msg);

  void WriteToSerial(mavlink_message_t* msg);
  void WriteToSerial(const vector<uint8_t>& bytes);

  serial::Serial serialPort_;

  Subscriber subWriteSerialAtt_;
  Publisher pubWriteSerialAtt_;

  Subscriber subWriteSerialTime_;
  Publisher pubWriteSerialTime_;  
};