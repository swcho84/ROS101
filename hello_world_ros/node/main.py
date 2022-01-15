#!/usr/bin/env python3

import rospy

from math import pi

def HelloWorldRos():
  rospy.init_node('hello_world_ros', anonymous=True)
  rate = rospy.Rate(100)

  while not rospy.is_shutdown():
    hello_str = "hello world %s" % rospy.get_time()
    rospy.loginfo(hello_str)
    rate.sleep()
  
if __name__ == '__main__':
  try:
    HelloWorldRos()
  except rospy.ROSInterruptException:
    pass
