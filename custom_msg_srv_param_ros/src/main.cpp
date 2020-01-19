#include "read_param.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "read_parameter_example_node");
  NodeHandle nh("");

  ReadParamTestNode readParamTestNode;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    readParamTestNode.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  readParamTestNode.~ReadParamTestNode();

  return 0;
}  // end main()