#include "pub_sinusoidal_signal_ros.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "sinusoidal_signal_publisher_node");
  NodeHandle nh("");

  PubSinusoidalSignalNode pubSinusoidalSignalNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    pubSinusoidalSignalNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  pubSinusoidalSignalNode.~PubSinusoidalSignalNode();

  return 0;
}  // end main()