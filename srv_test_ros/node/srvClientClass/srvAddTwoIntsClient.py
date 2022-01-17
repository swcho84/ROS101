#!/usr/bin/env python3
import rospy
from custom_msg_srv_param_ros.srv import AddTwoInts

class SrvClientAddTwoInt:
  def __init__(self):
    self.time = rospy.Time.now()
    self.x = 0
    self.y = 0

  def ClientAddTwoInts(self, strSrvNm, x, y, type):
    rospy.wait_for_service(strSrvNm)
    try:
        srvClient = rospy.ServiceProxy(strSrvNm, AddTwoInts)
        if (type == "inhouse"):
          res = srvClient(self.x, self.y)
        elif (type == "sys") | (type == "rosparam"):
          res = srvClient(x, y)
        else: 
          res = srvClient(x, y)
        return res.sum
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)		