#include "pub_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "publisher_test_node");
  NodeHandle nh("");

  PubTestNode pubTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    pubTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  return 0;
}  // end main()