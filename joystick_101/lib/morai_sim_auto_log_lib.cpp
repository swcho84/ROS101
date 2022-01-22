#include "morai_sim_auto_log_lib.h"

using namespace std;
using namespace ros;
using namespace cv;

MoraiAutoLog::MoraiAutoLog(const ConfigParam& cfg) : cfgParam_(cfg), it_(nh_)
{
}

MoraiAutoLog::~MoraiAutoLog()
{
}

// generating a set of the vehicle pose
vector<morai_msgs::MultiEgoSetting> MoraiAutoLog::ImgLogLoop(double dt, MoraiVehicleStatus vehicleState,
                                                             morai_msgs::ObjectStatusList objStatList)
{
  vector<morai_msgs::MultiEgoSetting> res;

  // assigning pedestrian status, lastone(in moraiSim) is first one
  vector<morai_msgs::ObjectStatus> vecPedStat;
  for (auto i = 0; i < objStatList.pedestrian_list.size(); i++)
    vecPedStat.push_back(objStatList.pedestrian_list[i]);

  // assigning object status, lastone(in moraiSim) is first one
  vector<morai_msgs::ObjectStatus> vecObjStat;
  for (auto i = objStatList.obstacle_list.size(); i-- != 0;)
    vecObjStat.push_back(objStatList.obstacle_list[i]);

  // setting the early stop condition
  // if ((vecPedStat.size() == 0) && (vecObjStat.size() == 0))
  //   return res;

  vector<morai_msgs::ObjectStatus> vecRef;
  nCenterNum_ = cfgParam_.nCenterObjNum;
  vecRef.assign(vecObjStat.begin(), vecObjStat.end());

  // P_e[1]	   =  sin(TrajectoryHeading)*(navstates.lcc[0] - PosRefLCC[0]) - cos(TrajectoryHeading)*(navstates.lcc[1] -
  // PosRefLCC[1]); // lateral direction error (leftside is positive(+) ) P_e[0]     =
  // -cos(TrajectoryHeading)*(navstates.lcc[0] - PosRefLCC[0]) - sin(TrajectoryHeading)*(navstates.lcc[1] -
  // PosRefLCC[1]); // longitudinal direction error (backside is positive(+) )

  double dRref = 6.0;
  vector<RelObjStatus> vecRelObjStatus;
  for (auto i = 0; i < vecRef.size(); i++)
  {
    RelObjStatus tempRelObjStat;
    tempRelObjStat.dRelHead = vehicleState.dHeadAng - vecRef[i].heading;
    tempRelObjStat.dRelEuDist =
        sqrt(((vehicleState.dPosXNed - vecRef[i].position.x) * (vehicleState.dPosXNed - vecRef[i].position.x)) +
             ((vehicleState.dPosYNed - vecRef[i].position.y) * (vehicleState.dPosYNed - vecRef[i].position.y)));
    tempRelObjStat.strObjName = vecRef[i].name;
    tempRelObjStat.dRelXNed =
        vecRef[i].position.x +
        ((dRref) / (tempRelObjStat.dRelEuDist)) * (-(vehicleState.dPosXNed - vecRef[i].position.x) * sin(90 * D2R) +
                                                   (vehicleState.dPosYNed - vecRef[i].position.y) * cos(90 * D2R));
    tempRelObjStat.dRelYNed =
        vecRef[i].position.y -
        ((dRref) / (tempRelObjStat.dRelEuDist)) * ((vehicleState.dPosXNed - vecRef[i].position.x) * cos(90 * D2R) -
                                                   (vehicleState.dPosYNed - vecRef[i].position.y) * sin(90 * D2R));
    tempRelObjStat.dRelZNed = vehicleState.dPosZNed;
    vecRelObjStatus.push_back(tempRelObjStat);
  }

  for (auto i = 0; i < vecRelObjStatus.size(); i++)
    ROS_INFO("Rel[%d](%s)(%.4f,%.4f,%.4f,%.4f,%.4f)", (int)(i), vecRelObjStatus[i].strObjName.c_str(),
             vecRelObjStatus[i].dRelXNed, vecRelObjStatus[i].dRelYNed, vecRelObjStatus[i].dRelZNed,
             vecRelObjStatus[i].dRelHead, vecRelObjStatus[i].dRelEuDist);

  if (vecRelObjStatus.size() > 0)
  {
    morai_msgs::MultiEgoSetting resTemp;
    resTemp.ego_index.resize(1);
    resTemp.global_position_x.resize(1);
    resTemp.global_position_y.resize(1);
    resTemp.global_position_z.resize(1);
    resTemp.global_roll.resize(1);
    resTemp.global_pitch.resize(1);
    resTemp.global_yaw.resize(1);
    resTemp.velocity.resize(1);
    resTemp.gear.resize(1);
    resTemp.ctrl_mode.resize(1);
    resTemp.number_of_ego_vehicle = 1;
    resTemp.camera_index = 0;
    resTemp.ego_index[0] = 0;
    resTemp.global_position_x[0] = vecRelObjStatus[0].dRelXNed;
    resTemp.global_position_y[0] = vecRelObjStatus[0].dRelYNed;
    resTemp.global_position_z[0] = vecRelObjStatus[0].dRelYNed;
    resTemp.global_roll[0] = 0.0;
    resTemp.global_pitch[0] = 0.0;
    resTemp.global_yaw[0] = vehicleState.dHeadAng * D2R;
    resTemp.velocity[0] = 0.0;
    resTemp.gear[0] = PGEAR;
    resTemp.ctrl_mode[0] = 16;  // automode
    res.push_back(resTemp);
  }

  return res;
}

// generating the reference pose, heading
morai_msgs::MultiEgoSetting MoraiAutoLog::CalcRefHeadPoseFwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                             MoraiVehicleStatus vehicleState, float fDistYRef,
                                                             float fDistXRef, float fSign, float fDiffHead)
{
  morai_msgs::MultiEgoSetting res;

  float fXref, fYref, fHeadRef = 0.0f;
  if (fSign > 0)
  {
    fXref = (vecRef[nCenterNum_].position.x + ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y - ((fDistYRef) / (sqrt(2))) * (2.0f));
    fHeadRef = (vehicleState.dHeadAng) * (R2D) + (fDiffHead);
  }
  else
  {
    fXref = (vecRef[nCenterNum_].position.x - ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y - ((fDistYRef) / (sqrt(2))) * (2.0f));
    fHeadRef = (vehicleState.dHeadAng) * (R2D) - (fDiffHead);
  }

  float fZref = vehicleState.dPosZNed;
  res.ego_index.resize(1);
  res.global_position_x.resize(1);
  res.global_position_y.resize(1);
  res.global_position_z.resize(1);
  res.global_roll.resize(1);
  res.global_pitch.resize(1);
  res.global_yaw.resize(1);
  res.velocity.resize(1);
  res.gear.resize(1);
  res.ctrl_mode.resize(1);
  res.number_of_ego_vehicle = 1;
  res.camera_index = 0;
  res.ego_index[0] = 0;
  res.global_position_x[0] = fXref;
  res.global_position_y[0] = fYref;
  res.global_position_z[0] = fZref;
  res.global_roll[0] = 0.0;
  res.global_pitch[0] = 0.0;
  res.global_yaw[0] = fHeadRef;
  res.velocity[0] = 0.0;
  res.gear[0] = PGEAR;
  res.ctrl_mode[0] = 16;  // automode
  return res;
}

// generating the reference pose, x-axis
morai_msgs::MultiEgoSetting MoraiAutoLog::CalcRefXPoseFwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                          MoraiVehicleStatus vehicleState, float fDistYRef,
                                                          float fDistXRef, float fSign)
{
  morai_msgs::MultiEgoSetting res;

  float fXref, fYref = 0.0f;
  if (fSign > 0)
  {
    fXref = (vecRef[nCenterNum_].position.x + ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y - ((fDistYRef) / (sqrt(2))) * (2.0f));
  }
  else
  {
    fXref = (vecRef[nCenterNum_].position.x - ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y - ((fDistYRef) / (sqrt(2))) * (2.0f));
  }

  float fZref = vehicleState.dPosZNed;
  float fHeadRef = (vehicleState.dHeadAng) * (R2D);
  res.ego_index.resize(1);
  res.global_position_x.resize(1);
  res.global_position_y.resize(1);
  res.global_position_z.resize(1);
  res.global_roll.resize(1);
  res.global_pitch.resize(1);
  res.global_yaw.resize(1);
  res.velocity.resize(1);
  res.gear.resize(1);
  res.ctrl_mode.resize(1);
  res.number_of_ego_vehicle = 1;
  res.camera_index = 0;
  res.ego_index[0] = 0;
  res.global_position_x[0] = fXref;
  res.global_position_y[0] = fYref;
  res.global_position_z[0] = fZref;
  res.global_roll[0] = 0.0;
  res.global_pitch[0] = 0.0;
  res.global_yaw[0] = fHeadRef;
  res.velocity[0] = 0.0;
  res.gear[0] = PGEAR;
  res.ctrl_mode[0] = 16;  // automode
  return res;
}

// generating the reference pose, y-axis
morai_msgs::MultiEgoSetting MoraiAutoLog::CalcRefYPoseFwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                          MoraiVehicleStatus vehicleState, float fDistRef)
{
  morai_msgs::MultiEgoSetting res;
  float fSameDiff = (fDistRef) / (sqrt(2));
  float fXref = (vecRef[nCenterNum_].position.x - (fSameDiff) / (2.0f));
  float fYref = (vecRef[nCenterNum_].position.y - (2.0f) * (fSameDiff));
  float fZref = vehicleState.dPosZNed;
  float fHeadRef = (vehicleState.dHeadAng) * (R2D);
  res.ego_index.resize(1);
  res.global_position_x.resize(1);
  res.global_position_y.resize(1);
  res.global_position_z.resize(1);
  res.global_roll.resize(1);
  res.global_pitch.resize(1);
  res.global_yaw.resize(1);
  res.velocity.resize(1);
  res.gear.resize(1);
  res.ctrl_mode.resize(1);
  res.number_of_ego_vehicle = 1;
  res.camera_index = 0;
  res.ego_index[0] = 0;
  res.global_position_x[0] = fXref;
  res.global_position_y[0] = fYref;
  res.global_position_z[0] = fZref;
  res.global_roll[0] = 0.0;
  res.global_pitch[0] = 0.0;
  res.global_yaw[0] = fHeadRef;
  res.velocity[0] = 0.0;
  res.gear[0] = PGEAR;
  res.ctrl_mode[0] = 16;  // automode
  return res;
}

// generating the reference pose, heading
morai_msgs::MultiEgoSetting MoraiAutoLog::CalcRefHeadPoseBwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                             MoraiVehicleStatus vehicleState, float fDistYRef,
                                                             float fDistXRef, float fSign, float fDiffHead)
{
  morai_msgs::MultiEgoSetting res;

  float fXref, fYref, fHeadRef = 0.0f;
  if (fSign > 0)
  {
    fXref = (vecRef[nCenterNum_].position.x + ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y + ((fDistYRef) / (sqrt(2))) * (2.0f));
    fHeadRef = (vehicleState.dHeadAng) * (R2D) + (fDiffHead);
  }
  else
  {
    fXref = (vecRef[nCenterNum_].position.x - ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y + ((fDistYRef) / (sqrt(2))) * (2.0f));
    fHeadRef = (vehicleState.dHeadAng) * (R2D) - (fDiffHead);
  }

  float fZref = vehicleState.dPosZNed;
  res.ego_index.resize(1);
  res.global_position_x.resize(1);
  res.global_position_y.resize(1);
  res.global_position_z.resize(1);
  res.global_roll.resize(1);
  res.global_pitch.resize(1);
  res.global_yaw.resize(1);
  res.velocity.resize(1);
  res.gear.resize(1);
  res.ctrl_mode.resize(1);
  res.number_of_ego_vehicle = 1;
  res.camera_index = 0;
  res.ego_index[0] = 0;
  res.global_position_x[0] = fXref;
  res.global_position_y[0] = fYref;
  res.global_position_z[0] = fZref;
  res.global_roll[0] = 0.0;
  res.global_pitch[0] = 0.0;
  res.global_yaw[0] = fHeadRef;
  res.velocity[0] = 0.0;
  res.gear[0] = PGEAR;
  res.ctrl_mode[0] = 16;  // automode
  return res;
}

// generating the reference pose, x-axis
morai_msgs::MultiEgoSetting MoraiAutoLog::CalcRefXPoseBwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                          MoraiVehicleStatus vehicleState, float fDistYRef,
                                                          float fDistXRef, float fSign)
{
  morai_msgs::MultiEgoSetting res;

  float fXref, fYref = 0.0f;
  if (fSign > 0)
  {
    fXref = (vecRef[nCenterNum_].position.x + ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y + ((fDistYRef) / (sqrt(2))) * (2.0f));
  }
  else
  {
    fXref = (vecRef[nCenterNum_].position.x - ((fDistXRef) / (sqrt(2))) / (2.0f));
    fYref = (vecRef[nCenterNum_].position.y + ((fDistYRef) / (sqrt(2))) * (2.0f));
  }

  float fZref = vehicleState.dPosZNed;
  float fHeadRef = (vehicleState.dHeadAng) * (R2D);
  res.ego_index.resize(1);
  res.global_position_x.resize(1);
  res.global_position_y.resize(1);
  res.global_position_z.resize(1);
  res.global_roll.resize(1);
  res.global_pitch.resize(1);
  res.global_yaw.resize(1);
  res.velocity.resize(1);
  res.gear.resize(1);
  res.ctrl_mode.resize(1);
  res.number_of_ego_vehicle = 1;
  res.camera_index = 0;
  res.ego_index[0] = 0;
  res.global_position_x[0] = fXref;
  res.global_position_y[0] = fYref;
  res.global_position_z[0] = fZref;
  res.global_roll[0] = 0.0;
  res.global_pitch[0] = 0.0;
  res.global_yaw[0] = fHeadRef;
  res.velocity[0] = 0.0;
  res.gear[0] = PGEAR;
  res.ctrl_mode[0] = 16;  // automode
  return res;
}

// generating the reference pose, y-axis
morai_msgs::MultiEgoSetting MoraiAutoLog::CalcRefYPoseBwd(vector<morai_msgs::ObjectStatus> vecRef,
                                                          MoraiVehicleStatus vehicleState, float fDistRef)
{
  morai_msgs::MultiEgoSetting res;
  float fSameDiff = (fDistRef) / (sqrt(2));
  float fXref = (vecRef[nCenterNum_].position.x - (fSameDiff) / (2.0f));
  float fYref = (vecRef[nCenterNum_].position.y + (2.0f) * (fSameDiff));
  float fZref = vehicleState.dPosZNed;
  float fHeadRef = (vehicleState.dHeadAng) * (R2D);
  res.ego_index.resize(1);
  res.global_position_x.resize(1);
  res.global_position_y.resize(1);
  res.global_position_z.resize(1);
  res.global_roll.resize(1);
  res.global_pitch.resize(1);
  res.global_yaw.resize(1);
  res.velocity.resize(1);
  res.gear.resize(1);
  res.ctrl_mode.resize(1);
  res.number_of_ego_vehicle = 1;
  res.camera_index = 0;
  res.ego_index[0] = 0;
  res.global_position_x[0] = fXref;
  res.global_position_y[0] = fYref;
  res.global_position_z[0] = fZref;
  res.global_roll[0] = 0.0;
  res.global_pitch[0] = 0.0;
  res.global_yaw[0] = fHeadRef;
  res.velocity[0] = 0.0;
  res.gear[0] = PGEAR;
  res.ctrl_mode[0] = 16;  // automode
  return res;
}
