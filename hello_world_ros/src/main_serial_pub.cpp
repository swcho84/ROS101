#include "hello_serial_pub_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "hello_world_serial_publish_node");
  NodeHandle nh("");

  HelloSerialPubRos helloSerialPubRos;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    helloSerialPubRos.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  helloSerialPubRos.~HelloSerialPubRos();

  return 0;
}  // end main()