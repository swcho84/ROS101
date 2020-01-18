#include "pub_basic_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "basic_publisher_test_node");
  NodeHandle nh("");

  PubBasicTestNode pubBasicTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    pubBasicTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  pubBasicTestNode.~PubBasicTestNode();

  return 0;
}  // end main()