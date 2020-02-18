#include "hello_serial_sub_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "hello_world_serial_subscribe_node");
  NodeHandle nh("");

  HelloSerialSubRos helloSerialSubRos;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    helloSerialSubRos.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  helloSerialSubRos.~HelloSerialSubRos();

  return 0;
}  // end main()