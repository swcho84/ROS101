#include "pub_advanced_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "advanced_publisher_test_node");
  NodeHandle nh("");

  PubAdvancedTestNode pubAdvancedTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    pubAdvancedTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  pubAdvancedTestNode.~PubAdvancedTestNode();

  return 0;
}  // end main()