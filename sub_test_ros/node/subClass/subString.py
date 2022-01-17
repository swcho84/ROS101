import rospy
from std_msgs.msg import String

class SubString:
	def __init__(self):
		self.count = 0

	def GenSubscriber(self, strTpNm, cbloop):
		sub = rospy.Subscriber(strTpNm, String, cbloop)	
		return sub

	def CbString(self, data):
		rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)