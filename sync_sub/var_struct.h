#ifndef CAMIMG_LOGGER_VAR_STRUCT_H
#define CAMIMG_LOGGER_VAR_STRUCT_H

#include "global_header.h"

using namespace std;
using namespace ros;
using namespace cv;

typedef struct
{
  double dYear;
  double dMonth;
  double dDay;
  double dHour;
  double dMin;
  double dSec;
} TimeDB;

typedef struct
{
  Eigen::Vector3f linAcc;
  Eigen::Vector3f rotRate;
} BodyLinAccRotRate;

#endif