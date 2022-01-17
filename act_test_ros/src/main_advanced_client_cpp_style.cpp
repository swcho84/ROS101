#include "actionlib_advanced_client_test_ros.h"

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
  init(argc, argv, "action_advanced_client_test_ros_node");

  // calling the action, role: client
  ActionLibAdvancedClientRos actionLibAdvClientRos("averaging");
  signal(SIGINT, SigIntHandler);

  // gathering the result from the action server
  int nNumSize = 10;
  actionLibAdvClientRos.MainActionLoop(nNumSize);

  spin();

  return 0;
}  // end main()