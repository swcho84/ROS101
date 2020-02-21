#include "hello_serial_pub_ros.h"

using namespace std;
using namespace ros;

HelloSerialPubRos::HelloSerialPubRos()
{
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
  std_msgs::String msgString;
  msgString.data = "Hello, from ROS-seril comm!\n";
  serialPort.write(msgString.data);
}

bool HelloSerialPubRos::ConnectSerialPort()
{
  try
  {
    serialPort.setPort("/dev/ttyUSB0");
    serialPort.setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    serialPort.setTimeout(to);
    serialPort.open();
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR("Fail to open port../dev/ttyUSB0");
    return false;
  }

  if (serialPort.isOpen())
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