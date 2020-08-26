#include "img_grabcut_insert_lib.h"

using namespace std;
using namespace ros;
using namespace cv;

// using SIGINT handler
void SigIntHandler(int param)
{
  ROS_INFO("User pressed Ctrl+C..forced exit..");
  exit(1);
}

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "grabcut_insert_node");
  NodeHandle nh("");

  ImgGrabCutInsert imgGrabCutInsert;
  signal(SIGINT, SigIntHandler);

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  imgGrabCutInsert.MainLoop();

  spin();

  imgGrabCutInsert.~ImgGrabCutInsert();

  return 0;
}  // end main()