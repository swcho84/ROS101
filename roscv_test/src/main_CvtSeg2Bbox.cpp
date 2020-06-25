#include "CvtSeg2Bbox.h"

using namespace std;
using namespace ros;

/*--------------------------------------------------------------------
 * main()
 * Main function to set up ROS node.
 *------------------------------------------------------------------*/

int main(int argc, char** argv)
{
  // Set up ROS.
  init(argc, argv, "convert_segDB_to_BboxDB");
  NodeHandle nh("");

  CvtSeg2Bbox seg2Bbox;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    seg2Bbox.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  seg2Bbox.~CvtSeg2Bbox();

  return 0;
}  // end main()