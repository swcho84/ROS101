#include "joy_viewlink_ctrl_lib.h"

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
  init(argc, argv, "joy_viewlink_ctrl_node");
  NodeHandle nh("");

  // reading ros params
  ConfigParam cfg;
  if (!cfg.GetRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    return 0;
  }

  // initilaizing the tx loop
  ROS_INFO("Joystick Parsing Test Node");
  JoyViewLinkCtrl joyViewLinkCtrl(cfg);
  signal(SIGINT, SigIntHandler);

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    // main function
    joyViewLinkCtrl.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  joyViewLinkCtrl.~JoyViewLinkCtrl();
  return 0;
}  // end main()
