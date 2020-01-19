#include "sub_advanced_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "advanced_subscriber_test_node");
  NodeHandle nh("");

  SubAdvancedTestNode subAdvancedTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    subAdvancedTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  subAdvancedTestNode.~SubAdvancedTestNode();

  return 0;
}  // end main()