import rospy
import numpy as np
from std_msgs.msg import Float64MultiArray

class SubSineCurve:
	def __init__(self):
		self.time = 0.0
		self.sineData = 0.0

	def GenSubscriber(self, strTpNm, cbloop):
		sub = rospy.Subscriber(strTpNm, Float64MultiArray, cbloop)	
		return sub

	def CbSineCurve(self, msg):
		rospy.loginfo(msg.data)
		self.time = msg.data[0]
		self.sineData = msg.data[1]
		print(self.time, self.sineData)
		return	