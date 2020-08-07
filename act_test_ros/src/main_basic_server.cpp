#include "actionlib_basic_server_test_ros.h"

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
  init(argc, argv, "action_basic_test_ros_node");
  NodeHandle nh("");

  ActionLibBasicRos actionLibBasicRos("fibonacci");
  signal(SIGINT, SigIntHandler);

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    actionLibBasicRos.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  actionLibBasicRos.~ActionLibBasicRos();

  return 0;
}  // end main()