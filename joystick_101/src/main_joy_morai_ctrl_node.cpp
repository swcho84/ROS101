#include "joy_morai_ctrl_lib.h"

using namespace std;
using namespace ros;

// using SIGINT handler
void SigIntHandler(int param)
{
  ROS_INFO("User pressed Ctrl+C..forced exit..");
  exit(1);
}

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/
int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "joy_morai_ctrl_node");
  NodeHandle nh("");

  // reading ros params
  ConfigParam cfg;
  if (!cfg.GetRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    return 0;
  }

  // initilaizing the rx loop
  ROS_INFO("Joystick Control Command Generator Node for Morai Simulator");
  JoyMoraiCtrl joyMoralCtrl(cfg);
  signal(SIGINT, SigIntHandler);

  // Tell ROS how fast to run this node.
  Rate loopRate(100);

  // calculating dt info.
  ros::Time rosCurrTime, rosPrevTime;
  rosCurrTime = ros::Time::now();
  rosPrevTime = ros::Time::now();

  // Main loop.
  while (ok())
  {
    // generating the current time
    rosCurrTime = ros::Time::now();

    // main function
    double dt = (rosCurrTime - rosPrevTime).toSec();
    joyMoralCtrl.MainLoop(dt);

    // check for incoming messages
    spinOnce();
    loopRate.sleep();
    rosPrevTime = rosCurrTime;
  }

  return 0;
}  // end main()
