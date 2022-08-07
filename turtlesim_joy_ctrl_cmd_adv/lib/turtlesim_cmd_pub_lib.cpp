#include "turtlesim_cmd_pub_lib.h"

using namespace std;
using namespace ros;

TurtleSimCmdPubLib::TurtleSimCmdPubLib()
{
  // publisher, turtlesim control command, 2D, geometry msg
  pubTurtleCmd_ = nh_.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

  // service, turtlesim trajectory clear, client
  srvClientTrjClear_ = nh_.serviceClient<std_srvs::Empty>("/clear");
}

TurtleSimCmdPubLib::~TurtleSimCmdPubLib()
{
}

void TurtleSimCmdPubLib::MainLoop()
{
  // generating the joystick command
  joyTurtleSimCtrlCmd_ = joyXbox360_.GenJoyInfoLoop();

  // for debugging
  // ROS_INFO("rpy:(%.4lf,%.4lf,%.4lf)", joyTurtleSimCtrlCmd_.ctrlMove.fRoll, joyTurtleSimCtrlCmd_.ctrlMove.fPitch,
  // joyTurtleSimCtrlCmd_.ctrlMove.fYaw); ROS_INFO("throttle:(%.4lf)", joyTurtleSimCtrlCmd_.ctrlMove.fThr);
  // ROS_INFO("(auto,joy):(%d,%d)", (int)(joyTurtleSimCtrlCmd_.bCtrlAutoMode),
  // (int)(joyTurtleSimCtrlCmd_.bCtrlJoyMode)); ROS_INFO("feature(1,2):(%d,%d)", joyTurtleSimCtrlCmd_.nRgearStatus,
  // joyTurtleSimCtrlCmd_.nDgearStatus); ROS_INFO(" ");

  // clearing trajectories
  if (joyTurtleSimCtrlCmd_.nDgearStatus)
  {
    std_srvs::Empty srvEmpty;
    ROS_INFO("turtlesim trajecyory clear..");
    srvClientTrjClear_.call(srvEmpty);
  }

  // publishing joystick commands
  geometry_msgs::Twist msgTurtleCmd_;
  msgTurtleCmd_.linear.x = (-1.0) * (2.0) * (joyTurtleSimCtrlCmd_.ctrlMove.fPitch);
  msgTurtleCmd_.linear.y = 0.0;
  msgTurtleCmd_.linear.z = 0.0;
  msgTurtleCmd_.angular.x = 0.0;
  msgTurtleCmd_.angular.y = 0.0;
  msgTurtleCmd_.angular.z = (-1.0) * (2.0) * (joyTurtleSimCtrlCmd_.ctrlMove.fRoll);
  pubTurtleCmd_.publish(msgTurtleCmd_);
}
