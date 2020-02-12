#include "imgproc_lane_vehicle.h"

using namespace std;
using namespace ros;
using namespace cv;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "img_proc_101_node");
  NodeHandle nh("");

  ImgProc101 imgProc101;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    imgProc101.MainLoop();
	  
    cvWaitKey(30);
    spinOnce();
    loopRate.sleep();
  }

  imgProc101.~ImgProc101();

  return 0;
}  // end main()