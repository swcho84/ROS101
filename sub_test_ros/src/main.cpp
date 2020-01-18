#include "sub_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "subscriber_test_node");
  NodeHandle nh("");

  SubTestNode subTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    subTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  subTestNode.~SubTestNode();

  return 0;
}  // end main()