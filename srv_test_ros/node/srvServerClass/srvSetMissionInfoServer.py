#!/usr/bin/env python3
import rospy
from custom_msg_srv_param_ros.msg import Define
from custom_msg_srv_param_ros.srv import SetMissionInfo, SetMissionInfoResponse

class SrvServerSetMissionInfo:
  def __init__(self):
    self.time = rospy.Time.now()
    self.params = Define()

  def SetDict(self):
    res = {
			self.params.STATUS_A : self.SetInfo(0.0, 0.0, 0.0, (0.0) * (self.params.D2R), "absolute"),
			self.params.STATUS_B : self.SetInfo(10.0, 20.0, 30.0, (10.0) * (self.params.D2R), "absolute"),
			self.params.STATUS_C : self.SetInfo(30.0, 20.0, 10.0, (40.0) * (self.params.D2R), "relative"),
			self.params.STATUS_D : self.SetInfo(-10.0, -20.0, -10.0, (-30.0) * (self.params.D2R), "absolute")
		}
    return res

  def SetInfo(self, posX, posY, posZ, head, strType):
    res = SetMissionInfo()
    res.x_ref = posX
    res.y_ref = posY
    res.z_ref = posZ
    res.yaw_ref = (head) * (self.params.D2R)
    res.yaw_ref_type = strType
    return res

  def GetInfo(self, keyIn):
    res = SetMissionInfoResponse()
    res.x_ref = (self.SetDict().get(keyIn)).x_ref
    res.y_ref = (self.SetDict().get(keyIn)).y_ref
    res.z_ref = (self.SetDict().get(keyIn)).z_ref
    res.yaw_ref = (self.SetDict().get(keyIn)).yaw_ref
    res.yaw_ref_type = (self.SetDict().get(keyIn)).yaw_ref_type	
    return res

  def CbSetMissionInfo(self, req):
    res = SetMissionInfoResponse()
    if ((self.SetDict().get(req.mission_num)) == None):
      print("please check the mission info::default..")
      res = self.GetInfo(self.params.STATUS_A)
      return res 
    else:
      res = self.GetInfo(req.mission_num)
      print("set mission info(x_ref,y_ref,z_ref,yaw_ref,yaw_stat", 
						res.x_ref, res.y_ref, res.z_ref, res.yaw_ref, res.yaw_ref_type)
    return res

  def ServerSetMissionInfo(self, strSrvNm):
    srvServer = rospy.Service(strSrvNm, SetMissionInfo, self.CbSetMissionInfo)
    print("Ready to set mission info..")