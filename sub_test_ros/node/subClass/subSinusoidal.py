import rospy
import numpy as np
from std_msgs.msg import Float64

class SubSineCurve:
	def __init__(self):
		self.count = 0

	def GenSubscriber(self, strTpNm, cbloop):
		sub = rospy.Subscriber(strTpNm, Float64, cbloop)	
		return sub

	def CbSineCurve(self, data):
		rospy.loginfo(data.data)