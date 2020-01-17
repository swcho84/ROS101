#!/usr/bin/env python
import rospy
import std_msgs
from math import pi
from std_msgs.msg import String

def HelloWorldRos():
  rospy.init_node('hello_world_ros', anonymous=True)
  rate = rospy.Rate(30)
  while not rospy.is_shutdown():
    hello_str = "hello world %s" % rospy.get_time()
    rospy.loginfo(hello_str)
    rate.sleep()
  
if __name__ == '__main__':
  try:
    HelloWorldRos()
  except rospy.ROSInterruptException:
    pass