// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

// using serial library
#include <serial/serial.h>

// for using standard messages
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>

// for using custom mavlink
#include <mavlink_types.h>
#include <cju_swcho/mavlink.h>

using namespace std;
using namespace ros;

typedef enum {
  LIGHTBRIDGE = 0,
  SERIAL = 1,
  WEBSOCKET = 2,
} TMTC_CHANNEL;
  
class HelloSerialSubRos
{
public:
  HelloSerialSubRos();
  ~HelloSerialSubRos();

  bool ConnectSerialPort();

  void MainLoop();  

private:
  void HelloFunction();
  void Parse(const vector<uint8_t>& recv, TMTC_CHANNEL ch);
  void HandleTmDebugAtt(TMTC_CHANNEL ch, const mavlink_message_t& rx);
  void HandleTmDebugTime(TMTC_CHANNEL ch, const mavlink_message_t& rx);  
  serial::Serial serialPort_;
};