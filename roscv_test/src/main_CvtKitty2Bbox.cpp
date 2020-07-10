#include "CvtKitty2Bbox.h"

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
  init(argc, argv, "convert_kittyDB_to_bboxDB");
  NodeHandle nh("");

  // reading ros params
  ConfigParam cfg;
  if (!cfg.GetRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    return 0;
  }

  // converting annotated segmentation DB to bboxs with SIGINT handler
  CvtKtt2Bbox ktt2Bbox(cfg);
  signal(SIGINT, SigIntHandler);

  // Tell ROS how fast to run this node.
  Rate loopRate(30);

  // Main loop.
  while (ok())
  {
    ktt2Bbox.MainLoopBboxGenerator();

    spinOnce();
    loopRate.sleep();
  }

  ktt2Bbox.~CvtKtt2Bbox();
  ROS_INFO("Work Done: convert_kittyDB_to_bboxDB");

  return 0;
}  // end main()
