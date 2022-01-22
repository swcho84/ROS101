#ifndef JOYSTICK_101_MORAI_SIM_AUTO_LOG_LIB_H
#define JOYSTICK_101_MORAI_SIM_AUTO_LOG_LIB_H

#include "global_header.h"
#include "config_param.h"

using namespace std;
using namespace ros;
using namespace cv;

class MoraiAutoLog
{
public:
  MoraiAutoLog(const ConfigParam& cfg);
  ~MoraiAutoLog();

  vector<morai_msgs::MultiEgoSetting> ImgLogLoop(double dt, MoraiVehicleStatus vehicleState,
                                                 morai_msgs::ObjectStatusList objStatList);
  morai_msgs::MultiEgoSetting CalcRefYPoseFwd(vector<morai_msgs::ObjectStatus> vecRef, MoraiVehicleStatus vehicleState,
                                              float fDistRef);
  morai_msgs::MultiEgoSetting CalcRefXPoseFwd(vector<morai_msgs::ObjectStatus> vecRef, MoraiVehicleStatus vehicleState,
                                              float fDistYRef, float fDistXRef, float fSign);
  morai_msgs::MultiEgoSetting CalcRefHeadPoseFwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                 MoraiVehicleStatus vehicleState, float fDistYRef, float fDistXRef,
                                                 float fSign, float fDiffHead);
  morai_msgs::MultiEgoSetting CalcRefYPoseBwd(vector<morai_msgs::ObjectStatus> vecRef, MoraiVehicleStatus vehicleState,
                                              float fDistRef);
  morai_msgs::MultiEgoSetting CalcRefXPoseBwd(vector<morai_msgs::ObjectStatus> vecRef, MoraiVehicleStatus vehicleState,
                                              float fDistYRef, float fDistXRef, float fSign);
  morai_msgs::MultiEgoSetting CalcRefHeadPoseBwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                 MoraiVehicleStatus vehicleState, float fDistYRef, float fDistXRef,
                                                 float fSign, float fDiffHead);

private:
  ConfigParam cfgParam_;
  int nCenterNum_;

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
};

#endif  // JOYSTICK_101_MORAI_SIM_AUTO_LOG_LIB_H