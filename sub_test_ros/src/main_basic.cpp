#include "sub_basic_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "basic_subscriber_test_node");
  NodeHandle nh("");

  SubBasicTestNode subBasicTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    subBasicTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  subBasicTestNode.~SubBasicTestNode();

  return 0;
}  // end main()