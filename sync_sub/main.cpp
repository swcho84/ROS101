#include "mynteye_img_logger_lib.h"

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
  init(argc, argv, "camera_image_logger_node");
  NodeHandle nh("");

  // reading ros params
  ConfigParam cfg;
  if (!cfg.GetRosParams())
  {
    ROS_ERROR("Wrong params!! Please check the parameter sheet..");
    return 0;
  }

  // main class for mynteye stereo camera
  MyntEyeImgLogger myntEyeImgLogger(cfg);

  // Tell ROS how fast to run this node.
  Rate loopRate(60);

  // for calculating dt
  cfg.rosCurrTime = ros::Time::now();
  cfg.rosLastTime = ros::Time::now();

  // Main loop.
  while (ok())
  {
    // check for incoming messages
    spinOnce();
    
    cfg.rosCurrTime = ros::Time::now();
    cfg.dt = (cfg.rosCurrTime - cfg.rosLastTime).toSec();

    // main loop for mynteye camera
    myntEyeImgLogger.MainLoop(cfg.dt);

    cfg.rosLastTime = ros::Time::now();
    loopRate.sleep();
  }

  return 0;
}  // end main()
