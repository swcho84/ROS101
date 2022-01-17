#!/usr/bin/env python3
import rospy
from custom_msg_srv_param_ros.msg import Define
from custom_msg_srv_param_ros.srv import SetMissionInfo

class SrvClientSetMissionInfo:
  def __init__(self):
    self.time = rospy.Time.now()
    self.params = Define()
    self.missionNum = 0

  def ClientSetMissionInfo(self, strSrvNm, missionNum):
    rospy.wait_for_service(strSrvNm)
    try:
        srvClient = rospy.ServiceProxy(strSrvNm, SetMissionInfo)
        res = srvClient(missionNum)
        return res
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)		
