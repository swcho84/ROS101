#include "hello_serial_sub_ros.h"

using namespace std;
using namespace ros;

HelloSerialSubRos::HelloSerialSubRos()
{
}

HelloSerialSubRos::~HelloSerialSubRos()
{
}

void HelloSerialSubRos::MainLoop()
{
  HelloFunction();
}

void HelloSerialSubRos::HelloFunction()
{
  try
  {
    if (serialPort_.isOpen())
    {
      auto len = serialPort_.available();
      auto buf = serialPort_.read(len);
      std::vector<uint8_t> serialrx(buf.begin(), buf.end());
      Parse(serialrx, TMTC_CHANNEL::SERIAL);
    }
  }
  catch (serial::IOException)
  {
    ROS_ERROR("[Error] Failed to read from serial modem");
  }
}

void HelloSerialSubRos::HandleTmDebugTime(TMTC_CHANNEL ch, const mavlink_message_t& rx)
{
  auto time = mavlink_msg_tm_debug_time_get_time(&rx);

  // for debugging
  ROS_INFO("time(%f)", time);
}

void HelloSerialSubRos::HandleTmDebugAtt(TMTC_CHANNEL ch, const mavlink_message_t& rx)
{
  auto roll = mavlink_msg_tm_debug_att_get_roll(&rx);
  auto pitch = mavlink_msg_tm_debug_att_get_pitch(&rx);
  auto yaw = mavlink_msg_tm_debug_att_get_yaw(&rx);

  // for debugging
  ROS_INFO("att(%.4f,%.4f,%.4f)", roll, pitch, yaw);
}

void HelloSerialSubRos::Parse(const vector<uint8_t>& recv, TMTC_CHANNEL ch)
{
  mavlink_status_t status;
  mavlink_message_t rx;

  for (unsigned char i : recv)
  {
    if (mavlink_parse_char(MAVLINK_COMM_0 + ch, i, &rx, &status))
    {
      switch (rx.msgid)
      {
        case MAVLINK_MSG_ID_TM_DEBUG_TIME:
          HandleTmDebugTime(ch, rx);
          break;
        case MAVLINK_MSG_ID_TM_DEBUG_ATT:
          HandleTmDebugAtt(ch, rx);
          break;
        default:
          ROS_ERROR("Unsupported TC %d", rx.msgid);
          break;
      }
    }
  }
}

bool HelloSerialSubRos::ConnectSerialPort()
{
  try
  {
    serialPort_.setPort("/dev/ttyUSB1");
    serialPort_.setBaudrate(115200);
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    serialPort_.setTimeout(to);
    serialPort_.open();
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR("Fail to open port../dev/ttyUSB1");
    return false;
  }

  if (serialPort_.isOpen())
  {
    ROS_INFO("Serial Port initialized../dev/ttyUSB1");
    return true;
  }
  else
  {
    ROS_ERROR("Unable to open port../dev/ttyUSB1");
    return false;
  }
}