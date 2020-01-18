#include "srv_client_test_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "service_client_test_node");
  NodeHandle nh("");

  SrvClientTestNode srvClientTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    // testing calc_add_srv service
    // if (srvClientTestNode.CallAddSrvLoop())
    //   break;

    // testing set_mission_info service
    srvClientTestNode.MissionLoop();

    spinOnce();
    loopRate.sleep();
  }

  srvClientTestNode.~SrvClientTestNode();

  return 0;
}  // end main()