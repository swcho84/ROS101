// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <dirent.h> 

// essential header for ROS-OpenCV operation
#include <ros/ros.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace ros;

class CvtSeg2Bbox
{
public:
  CvtSeg2Bbox();
  ~CvtSeg2Bbox();

  void MainLoop();  

private:

};