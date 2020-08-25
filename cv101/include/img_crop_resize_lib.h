#ifndef CV101_IMG_CROP_RESIZE_LIB_H
#define CV101_IMG_CROP_RESIZE_LIB_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <vector>
#include <dirent.h>
#include <fstream>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace ros;
using namespace cv;

class ImgCropResize
{
public:
  ImgCropResize();
  ~ImgCropResize();

  void MainLoop();  

private:

};

#endif