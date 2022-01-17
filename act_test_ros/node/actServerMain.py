	#! /usr/bin/env python3
import rospy
import actServerClass.actFibonacciServer as actFibonacci
import actServerClass.actCalcMeanStdServer as actCalcMeanStd

def	MainActServerCalcMeanStd():
  rospy.loginfo("ActionServer::CalcMeanStd..activated")
  rospy.set_param("/calc_mean_std_sample", 10)
  actTest = actCalcMeanStd.ActServerAveraging()
  actServer = actTest.GenActionServerAveraging("/act_server_calc_mean_std", "/random_number")

def	MainActServerFibonacci():
  rospy.loginfo("ActionServer::Fibonacci..activated")
  rospy.set_param("/fibonacci_order", 10)
  actTest = actFibonacci.ActServerFibonacci()
  actServer = actTest.GenActionServerFibonacci("/act_server_fibonacci")

if __name__ == '__main__':
  try:
    rospy.init_node("ActionTestNode_Server", anonymous=True)
    MainActServerCalcMeanStd()
    rospy.spin()		
  except rospy.ROSInterruptException:
    pass