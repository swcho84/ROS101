#ifndef ROSCV_TEST_CVTKTTIY2BBOX_H
#define ROSCV_TEST_CVTKTTIY2BBOX_H

#include "global_header.h"
#include "config_param.h"

using namespace std;
using namespace ros;

class CvtKtt2Bbox
{
public:
  CvtKtt2Bbox(const ConfigParam& cfg);
  ~CvtKtt2Bbox();

  void MainLoopBboxGenerator();

private:
  ConfigParam cfgParam_;
  ColorStatus colorStat_;
  
};

#endif