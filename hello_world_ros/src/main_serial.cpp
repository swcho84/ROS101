#include "hello_serial_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "hello_world_serial_node");
  NodeHandle nh("");

  HelloSerialRos helloSerialRos;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    helloSerialRos.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  helloSerialRos.~HelloSerialRos();

  return 0;
}  // end main()