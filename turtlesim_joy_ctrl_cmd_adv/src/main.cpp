#include "turtlesim_cmd_pub_lib.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "turtlesim_cmd_pub_with_joystick_node");
  NodeHandle nh("");

  TurtleSimCmdPubLib turtleSimJoyCtrl;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    turtleSimJoyCtrl.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  turtleSimJoyCtrl.~TurtleSimCmdPubLib();

  return 0;
}  // end main()