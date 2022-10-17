#ifndef JOYSTICK_101_MISC_FUNC_H
#define JOYSTICK_101_MISC_FUNC_H

#include "global_header.h"
#include "config_param.h"

using namespace std;
using namespace ros;
using namespace Eigen;

class MiscFunc
{
public:
  MiscFunc(const ConfigParam& cfg);
  ~MiscFunc();

  Vector2d Calc2DPosErrInfo(Vector2d pos2DNedRef, Vector2d pos2DNedCurr, double dTrjHeading);
  Quaterniond CalcQuaternionFromYPREulerAng(Vector3d euler);
  Vector3d CalcYPREulerAngFromQuaternion(Quaterniond q);
  Matrix3d CalcDcmNtoB(Vector3d eulerAtt);
  Matrix3d CalcDcmBtoN(Vector3d eulerAtt);
  Matrix3d CalcDcmHeadingCtrl(float fYawRef);
  Matrix3d CalcDcmEuler321(Vector3d eulerAtt);
  Vector3d ConvertPosFromEnuToNed(Vector3d posEnu);
  Vector3d ConvertPosFromNedToEnu(Vector3d posNed);
  Matrix3d CalcDcmEnuToNed();
  Matrix3d CalcDcmNedToEnu();
  double wrapD(double _angle);

private:
  ConfigParam cfgParam_;
};

#endif  // JOYSTICK_101_MISC_FUNC_H