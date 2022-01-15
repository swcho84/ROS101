#!/usr/bin/env python3
import rospy
import subClass.subString as subString
import subClass.subSinusoidal as subSine

def MainSubSineLoop():
	subTest = subSine.SubSineCurve()
	sub = subTest.GenSubscriber("/pub_test_sine", subTest.CbSineCurve)

def MainSubStringLoop():
	subTest = subString.SubString()
	sub = subTest.GenSubscriber("/pub_test_string", subTest.CbString)

if __name__ == '__main__':
	try:
		rospy.init_node("SubTestNode", anonymous=True)
		MainSubSineLoop()
		rospy.spin()		
	except rospy.ROSInterruptException:
		pass