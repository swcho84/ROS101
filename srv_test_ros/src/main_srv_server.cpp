#include "srv_server_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "service_server_test_node");
  NodeHandle nh("");

  SrvServerTestNode srvServerTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    srvServerTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  srvServerTestNode.~SrvServerTestNode();

  return 0;
}  // end main()