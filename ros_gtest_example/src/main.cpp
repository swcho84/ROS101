#include "ros_gtest_example_lib.h"

using namespace std;
using namespace ros;

// using SIGINT handler
void SigIntHandler(int param) {
  ROS_INFO("User pressed Ctrl+C..forced exit..");
  exit(1);
}

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char **argv) {
  // Set up ROS and Google Test
  init(argc, argv, "ros_gtest_example_ros_side");
  NodeHandle nh("");

  // setting main function class
  ROS_INFO("ROS-GoogleTest example");
  RosGtestLib rosGtest;
  signal(SIGINT, SigIntHandler);

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop, only once
  bool bTestRes = rosGtest.MainLoop();

  if (bTestRes)
    ROS_INFO("Passed..");
  else
    ROS_INFO("Not paseed..please check your function..");

  // releasing class info.
  rosGtest.~RosGtestLib();

  return 0;
} // end main()