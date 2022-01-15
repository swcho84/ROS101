#!/usr/bin/env python3
import rospy
import pubClass.pubString as pubString

def MainLoop():
	rospy.init_node("PubTestNode", anonymous=True)
	rate = rospy.Rate(10) # [Hz]
	pubTest = pubString.PubString()
	pubStr = pubTest.GenPublisher("/pub_test")

	while not rospy.is_shutdown():
		rospy.loginfo("publish..")
		pubStr.publish(pubTest.PublishString("Test"))
		rate.sleep()	

if __name__ == '__main__':
	try:
		MainLoop()
	except rospy.ROSInterruptException:
		pass