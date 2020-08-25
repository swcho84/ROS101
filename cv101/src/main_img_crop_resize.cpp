#include "img_crop_resize_lib.h"

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
  init(argc, argv, "img_crop_resize_node");
  NodeHandle nh("");

  ImgCropResize imgCropResize;

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    imgCropResize.MainLoop();

    spinOnce();
    loopRate.sleep();
  }

  imgCropResize.~ImgCropResize();

  return 0;
}  // end main()