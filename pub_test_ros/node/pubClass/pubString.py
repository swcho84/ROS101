import rospy
from std_msgs.msg import String

class PubString:
	def __init__(self):
		self.count = 0

	def GenPublisher(self, strTpNm):
		pub = rospy.Publisher(strTpNm, String, queue_size=1)	
		return pub

	def PublishString(self, strTarget):
		self.count += 1
		res = strTarget + " %d" % self.count + " %s" % rospy.get_time()
		return res