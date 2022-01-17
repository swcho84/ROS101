#!/usr/bin/env python3
import rospy
from custom_msg_srv_param_ros.srv import AddTwoInts, AddTwoIntsResponse

class SrvServerAddTwoInt:
  def __init__(self):
    self.time = rospy.Time.now()

  def CbAddTwoInts(self, req):
    res = AddTwoIntsResponse()
    res.sum = req.a + req.b
    print("FromClient:Returning[%s + %s = %s]"%(req.a, req.b, res.sum))
    return res

  def ServerAddTwoInts(self, strSrvNm):
    srvServer = rospy.Service(strSrvNm, AddTwoInts, self.CbAddTwoInts)
    print("Ready to add two ints..")