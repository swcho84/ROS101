#include "srv_server_test_ros.h"

using namespace std;
using namespace ros;
using namespace custom_msg_srv_param_ros;

SrvServerTestNode::SrvServerTestNode()
{
  srvServerCalcAdd_ = nh_.advertiseService("calc_add_srv", &SrvServerTestNode::CalcAddSrv, this);
  ROS_INFO("setup add calculation service");

  srvServerSetMissionInfo_ = nh_.advertiseService("set_mission_info_srv", &SrvServerTestNode::SetMissionInfoSrv, this);
  ROS_INFO("setup mission info generation service");
}

SrvServerTestNode::~SrvServerTestNode()
{
}

bool SrvServerTestNode::CalcAddSrv(AddTwoInts::Request& req, AddTwoInts::Response& res)
{
  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

bool SrvServerTestNode::SetMissionInfoSrv(SetMissionInfo::Request& req, SetMissionInfo::Response& res)
{
  ROS_INFO("request mission number:(%d)", (int)(req.mission_num));
  switch ((int)(req.mission_num))
  {
    case Define::STATUS_B:
    {
      res.x_ref = 10.0;
      res.y_ref = 20.0;
      res.z_ref = 30.0;
      res.yaw_ref = (10.0) * (Define::D2R);
      res.yaw_ref_type = "absolute";
      ROS_INFO("mission_1");
      break;
    }
    case Define::STATUS_C:
    {
      res.x_ref = 30.0;
      res.y_ref = 20.0;
      res.z_ref = 10.0;
      res.yaw_ref = (40.0) * (Define::D2R);
      res.yaw_ref_type = "relative";
      ROS_INFO("mission_2");
      break;
    }
    case Define::STATUS_D:
    {
      res.x_ref = -10.0;
      res.y_ref = -20.0;
      res.z_ref = -30.0;
      res.yaw_ref = (-30.0) * (Define::D2R);
      res.yaw_ref_type = "absolute";
      ROS_INFO("mission_3");
      break;
    }
    case Define::STATUS_A:
    default:
    {
      res.x_ref = 0.0;
      res.y_ref = 0.0;
      res.z_ref = 0.0;
      res.yaw_ref = (0.0) * (Define::D2R);
      res.yaw_ref_type = "absolute";
      ROS_INFO("mission_default");
      break;
    }
  }

  ROS_INFO("set mission info(x_ref,y_ref,z_ref,yaw_ref,yaw_stat)=(%.4f,%.4f,%.4f,%.4f,%s", res.x_ref, res.y_ref,
           res.z_ref, res.yaw_ref, res.yaw_ref_type.c_str());
  return true;
}

void SrvServerTestNode::MainLoop()
{
  ROS_INFO_DELAYED_THROTTLE(10, "ready to client..");
}
