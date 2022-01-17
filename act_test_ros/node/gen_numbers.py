#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32
import random

def GenRandNumber():
  pub = rospy.Publisher('random_number', Float32, queue_size=1)
  rospy.init_node('random_number_generator', log_level=rospy.INFO)
  rospy.loginfo("Generating random numbers")
  while not rospy.is_shutdown():
    pub.publish(Float32(random.normalvariate(5, 1)))
    rospy.sleep(1)

if __name__ == '__main__':
  try:
    GenRandNumber()
  except rospy.ROSInterruptException:
    pass
