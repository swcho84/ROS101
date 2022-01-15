#!/usr/bin/env python3
import rospy

def HelloWorldRos():
  rate = rospy.Rate(100)

  while not rospy.is_shutdown():
    hello_str = "hello world %s" % rospy.get_time()
    rospy.loginfo(hello_str)
    rate.sleep()
  
if __name__ == '__main__':
  try:
    rospy.init_node('hello_world_ros', anonymous=True)
    HelloWorldRos()
    rospy.spin()
  except rospy.ROSInterruptException:
    pass
