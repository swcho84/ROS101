#ifndef CV101_IMG_MIX_LIB_H
#define CV101_IMG_MIX_LIB_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <random>
#include <algorithm>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace ros;
using namespace cv;

typedef struct
{
  Point ptPixel;
  uchar blue;
  uchar green;
  uchar red;
} SelectRGB;

typedef struct
{
  int nWidth;
  int nHeight;
} ImgSize;

class ImgMix
{
public:
  ImgMix();
  ~ImgMix();

  void MainLoop();

private:
  Mat GetImgFromFile(string strBaseImgName);
  ImgSize GetImgSize(Mat imgInput);
  Mat GetImgTargetResized(Mat imgTarget, ImgSize imgTargetSize, ImgSize imgBaseSize, float fWidthRatio,
                          float fHeightRatio);
  int GenRandNum(int nSize);
  Point GetRngPtTlForTargetResized(ImgSize imgTargetResizedSize, ImgSize imgBaseSize, float fRatio);
  vector<SelectRGB> GetMaskInfo(Mat imgTargetResized, ImgSize imgTargetResizedSize);
  Mat GetImgMix(Mat imgInput, vector<SelectRGB> vecInput, Point ptInput, string strCmd);
  vector<Rect> GetTargetRect(Mat imgInput);
  static bool sortArea(cv::Rect rect1, cv::Rect rect2);

  Mat imgBase_;
  ImgSize imgBaseSize_;

  Mat imgTarget_;
  ImgSize imgTargetSize_;

  Mat imgTargetResized_;
  ImgSize imgTargetResizedSize_;

  Point ptRndTargetResizedPos_;
  vector<SelectRGB> vecSelectPixelMask_;

  Mat imgForMix_;
  Mat imgForContour_;
  Mat imgMixed_;

  vector<Rect> vecRectTarget_;
};

#endif
