#ifndef ROSCV_TEST_CVTSEG2BBOX_H
#define ROSCV_TEST_CVTSEG2BBOX_H

#include "global_header.h"
#include "config_param.h"

using namespace std;
using namespace ros;

class CvtSeg2Bbox
{
public:
  CvtSeg2Bbox(const ConfigParam& cfg);
  ~CvtSeg2Bbox();

  void MainLoopBboxGenerator();
  void MainLoopBboxChecker();
  bool GetSizeCalcFlag();

  bool bSizeCalcFlag;

private:
  ConfigParam cfgParam_;
  ColorStatus colorStat_;

  bool GenSizeCalcFlag(int nSize, int nTotal);
  Mat GenFilteredImg(Mat imgIn, int nHeight, int nWidth, int nAnno, int nTrial);
  Mat CannyEdge(Mat imgIn, int nThresh);
  vector<Rect> GenBboxData(Mat imgIn, Scalar color, int nThresh);

  int nHeight;
  int nWidth;
};

#endif