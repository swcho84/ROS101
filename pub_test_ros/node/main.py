#!/usr/bin/env python3
import rospy
import pubClass.pubString as pubString
import pubClass.pubSinusoidal as pubSine
import pubClass.pubCustomMultiArr as pubCustomArray

def MainLoopCustomArray():
	rate = rospy.Rate(30) # [Hz]
	pubTest = pubCustomArray.PubBboxArray()
	pubStr = pubTest.GenPublisher("/pub_test_custom_multi_array")

	while not rospy.is_shutdown():
		rospy.loginfo("publish..")
		pubStr.publish(pubTest.PubBboxArray(5))
		rate.sleep()	

def MainLoopSinusoidal():
	hz = 10
	rate = rospy.Rate(hz) # [Hz]
	pubTest = pubSine.PubSineCurve()
	pubStr = pubTest.GenPublisher("/pub_test_sine")
	prevTime = rospy.Time.now()
	nowTime = 0.0

	while not rospy.is_shutdown():
		rospy.loginfo("publish..")
		dt = (rospy.Time.now()  - prevTime).to_sec()
		nowTime += dt
		print(nowTime, dt)
		t, sinRes = pubTest.GenSine(hz, 1.0, nowTime, 0.0)
		pubStr.publish(pubTest.PubSine(t, sinRes))
		prevTime = rospy.Time.now()
		rate.sleep()	

def MainLoopString():
	rate = rospy.Rate(10) # [Hz]
	pubTest = pubString.PubString()
	pubStr = pubTest.GenPublisher("/pub_test_string")

	while not rospy.is_shutdown():
		rospy.loginfo("publish..")
		pubStr.publish(pubTest.PublishString("Test"))
		rate.sleep()	

if __name__ == '__main__':
	try:
		rospy.init_node("PubTestNode", anonymous=True)
		MainLoopCustomArray()
		rospy.spin()		
	except rospy.ROSInterruptException:
		pass