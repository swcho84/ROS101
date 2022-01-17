import rospy
import numpy as np
from custom_msg_srv_param_ros.msg import RectArray
from custom_msg_srv_param_ros.msg import RectInfo

class SubBboxArray:
	def __init__(self):
		self.detect = False
		self.bboxes = RectArray()

	def GenSubscriber(self, strTpNm, cbloop):
		sub = rospy.Subscriber(strTpNm, RectArray, cbloop)	
		return sub

	def CbBboxArray(self, msg):
		self.detect = msg.bDetect
		self.bboxes = msg.vecRectArray
		print(self.detect, self.bboxes[0].nNum)
		return	