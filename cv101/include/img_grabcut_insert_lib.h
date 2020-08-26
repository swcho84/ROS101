#ifndef CV101_IMG_GRABCUT_INSERT_LIB_H
#define CV101_IMG_GRABCUT_INSERT_LIB_H

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

class ImgGrabCutInsert
{
public:
  ImgGrabCutInsert();
  ~ImgGrabCutInsert();

  void MainLoop();

  static void CbMouseEvent(int event, int x, int y, int flags, void* that);
  void mouseClick(int event, int x, int y, int flags, Mat img);

private:
  void ResetRectLineData();

  bool bLtMousePressed_;
  bool bMdMousePressed_;

  int nInitRectX_;
  int nInitRectY_;
  int nCurrRectX_;
  int nCurrRectY_;

  int nInitLineX_;
  int nInitLineY_;
  int nCurrLineX_;
  int nCurrLineY_;

  Rect rectROI_;
  Point ptLineTl_;
  Point ptLineBr_;

  Mat imgRawFunc_;
  Mat imgRawGrabCut_;
  Mat markers_;
};

#endif
