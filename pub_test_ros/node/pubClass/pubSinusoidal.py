import rospy
import numpy as np
from std_msgs.msg import Float64

class PubSineCurve:
	def __init__(self):
		self.count = 0

	def GenPublisher(self, strTpNm):
		pub = rospy.Publisher(strTpNm, Float64, queue_size=1)	
		return pub

	def PubSine(self, hz, mag, t, bias):
		res = (mag) * (np.sin((2.0 * np.pi * hz * t) + bias)) 
		return res