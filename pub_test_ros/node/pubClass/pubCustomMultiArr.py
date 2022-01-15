import rospy
import numpy as np
from custom_msg_srv_param_ros.msg import RectArray
from custom_msg_srv_param_ros.msg import RectInfo

class PubBboxArray:
	def __init__(self):
		self.count = 0

	def GenPublisher(self, strTpNm):
		pub = rospy.Publisher(strTpNm, RectArray, queue_size=1)	
		return pub

	def GenBboxInfo(self, temp):
		res = RectInfo()
		res.nNum = temp
		res.fXlt = (10.0) * (temp)
		res.fYlt = (20.0) * (temp)
		res.fWidth = (30.0) * (temp)
		res.fHeight = (40.0) * (temp)
		res.fScore = (50.0) * (temp)		
		return res

	def PubBboxArray(self, size):
		msgRes = RectArray()
		for i in range(size):
			temp = self.GenBboxInfo(i)
			msgRes.bDetect = True
			msgRes.nStatus = 1
			msgRes.vecRectArray.append(temp)
		return msgRes