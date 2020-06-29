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

  void MainLoop();  

private:
  ConfigParam cfgParam_;

  Mat GenFilteredImg(Mat imgIn, int nHeight, int nWidth, int nAnno, int nTrial);
  Mat CannyEdge(Mat imgIn, int nThresh);
  vector<Rect> GenBboxData(Mat imgIn, Scalar color, int nThresh);
  
};

#endif