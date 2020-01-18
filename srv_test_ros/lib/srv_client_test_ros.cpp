#include "srv_client_test_ros.h"

using namespace std;
using namespace ros;

SrvClientTestNode::SrvClientTestNode()
  : nNum1_(0)
  , nNum2_(0)
  , nSumRes_(0)
  , nMissionNum_(0)
  , bMissionPerfStat_(false)
  , bMissionSetStat_(false)
  , dXref_(0.0f)
  , dYref_(0.0f)
  , dZref_(0.0f)
  , dYawRef_(0.0f)
  , strYawRef_("absolute")
{
  // saving parameters
  ReadParam();

  // setting service client
  srvClientAdd_ = nh_.serviceClient<srv_test_ros::AddTwoInts>("calc_add_srv");
  srvClientSetMissionInfo_ = nh_.serviceClient<srv_test_ros::SetMissionInfo>("set_mission_info_srv");

  // for debugging
  ROS_INFO("num(1,2):(%d,%d)", nNum1_, nNum2_);
  ROS_INFO("mission_num:(%d)", nMissionNum_);
}

SrvClientTestNode::~SrvClientTestNode()
{
}

void SrvClientTestNode::ReadParam()
{
  nh_.getParam("num1", nNum1_);
  nh_.getParam("num2", nNum2_);
}

void SrvClientTestNode::MissionLoop()
{
  // bMissionPerfStat_, false: during mission, true: end mission
  // bMissionSetStat_, true: set mission if bMissionPerfStat_ is true

  if (!bMissionPerfStat_)
  {
    ROS_INFO("Perform Mission:(x_ref,y_ref,z_ref,yaw_ref,yaw_stat)=(%.4f,%.4f,%.4f,%.4f,%s", dXref_, dYref_, dZref_,
             dYawRef_, strYawRef_.c_str());
    bMissionSetStat_ = true;
  }
  else
  {
    // setting mission number
    nh_.getParam("mission_num", nMissionNum_);

    // setting request info
    srv_test_ros::SetMissionInfo srvSetMissionInfo;
    srvSetMissionInfo.request.mission_num = nMissionNum_;

    // setting mission info just once
    if (bMissionSetStat_)
    {
      // calling set_mission_info_srv
      srvClientSetMissionInfo_.call(srvSetMissionInfo);

      dXref_ = srvSetMissionInfo.response.x_ref;
      dYref_ = srvSetMissionInfo.response.y_ref;
      dZref_ = srvSetMissionInfo.response.z_ref;
      dYawRef_ = srvSetMissionInfo.response.yaw_ref;
      strYawRef_ = srvSetMissionInfo.response.yaw_ref_type;

      // for debugging
      ROS_DEBUG("End Mission: wait set mission info..");
      ROS_DEBUG("Success: set mission info(x_ref,y_ref,z_ref,yaw_ref,yaw_stat)=(%.4f,%.4f,%.4f,%.4f,%s", dXref_, dYref_,
                dZref_, dYawRef_, strYawRef_.c_str());

      bMissionSetStat_ = false;
    }

    // for debugging
    ROS_DEBUG_DELAYED_THROTTLE(10, "Waiting mission start..");
  }

  // setting mission status
  nh_.getParam("mission_perf_status", bMissionPerfStat_);
}

bool SrvClientTestNode::CallAddSrvLoop()
{
  srv_test_ros::AddTwoInts srvAddTwoInts;
  srvAddTwoInts.request.a = nNum1_;
  srvAddTwoInts.request.b = nNum2_;

  if (srvClientAdd_.call(srvAddTwoInts))
  {
    ROS_INFO("Sum: %d", (int)(srvAddTwoInts.response.sum));
    return true;
  }
  else
  {
    ROS_ERROR("Failed to call service calc_add_srv");
    return false;
  }
}
