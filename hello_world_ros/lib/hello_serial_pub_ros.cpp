#include "hello_serial_pub_ros.h"

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

HelloSerialPubRos::HelloSerialPubRos()
{
  subWriteSerialAtt_ = nh_.subscribe("/serial_write/attitude", 1, &HelloSerialPubRos::CbWriteToSerialAtt, this);
  pubWriteSerialAtt_ = nh_.advertise<std_msgs::Float32MultiArray>("/serial_write/attitude", 1);

  subWriteSerialTime_ = nh_.subscribe("/serial_write/time", 1, &HelloSerialPubRos::CbWriteToSerialTime, this);
  pubWriteSerialTime_ = nh_.advertise<std_msgs::Float64MultiArray>("/serial_write/time", 1);  
}

HelloSerialPubRos::~HelloSerialPubRos()
{
}

void HelloSerialPubRos::MainLoop()
{
  HelloFunction();
}

void HelloSerialPubRos::HelloFunction()
{
  // ros time
  double dSec = Time::now().toSec();

  // float data, from ROS to ROS for using callback function
  std_msgs::Float32MultiArray msgFloat32MultiArray;
  msgFloat32MultiArray.data.resize(3);
  msgFloat32MultiArray.data[0] = sin(Define::PI * 1.0f * dSec);
  msgFloat32MultiArray.data[1] = cos(Define::PI * 1.0f * dSec);
  msgFloat32MultiArray.data[2] = 10.0f;
  pubWriteSerialAtt_.publish(msgFloat32MultiArray);

  // double data, from ROS to ROS for using callback function
  std_msgs::Float64MultiArray msgFloat64MultiArray;
  msgFloat64MultiArray.data.resize(1);
  msgFloat64MultiArray.data[0] = dSec;
  pubWriteSerialTime_.publish(msgFloat64MultiArray);

  // for debugging
  ROS_INFO_DELAYED_THROTTLE(10, "writing serial data..");
}

void HelloSerialPubRos::CbWriteToSerialTime(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
  // using mavlink
  mavlink_message_t mav;
  mavlink_tm_debug_time_t msgTmDebugTime = {};
  msgTmDebugTime.time = msg->data[0];  
  mavlink_msg_tm_debug_time_encode(MAV_SYS_ID, COMP_ID, &mav, &msgTmDebugTime);
  WriteToSerial(&mav);
}

void HelloSerialPubRos::CbWriteToSerialAtt(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
  // using mavlink
  mavlink_message_t mav;
  mavlink_tm_debug_att_t msgTmDebugAtt = {};
  msgTmDebugAtt.roll = msg->data[0];
  msgTmDebugAtt.pitch = msg->data[1];
  msgTmDebugAtt.yaw = msg->data[2];
  mavlink_msg_tm_debug_att_encode(MAV_SYS_ID, COMP_ID, &mav, &msgTmDebugAtt);
  WriteToSerial(&mav);
}

void HelloSerialPubRos::WriteToSerial(mavlink_message_t* msg)
{
  uint8_t buf[sizeof(mavlink_message_t)];
  uint32_t len = mavlink_msg_to_send_buffer(buf, msg);
  vector<uint8_t> vec(buf, buf + len);
  WriteToSerial(vec);
}

void HelloSerialPubRos::WriteToSerial(const vector<uint8_t>& bytes)
{
  try
  {
    if (serialPort_.isOpen())
    {
      serialPort_.write(bytes);
    }
  }
  catch (serial::IOException)
  {
    ROS_ERROR("[Error] Serial write to gcs failed(telemetry)");
  }
  catch (serial::PortNotOpenedException)
  {
    ROS_ERROR("[Error] Serial port to gcs not opened(telemetry)");
  }
}

bool HelloSerialPubRos::ConnectSerialPort()
{
  try
  {
    serialPort_.setPort("/dev/ttyUSB0");
    serialPort_.setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    serialPort_.setTimeout(to);
    serialPort_.open();
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR("Fail to open port../dev/ttyUSB0");
    return false;
  }

  if (serialPort_.isOpen())
  {
    ROS_INFO("Serial Port initialized../dev/ttyUSB0");
    return true;
  }
  else
  {
    ROS_ERROR("Unable to open port../dev/ttyUSB0");
    return false;
  }
}