#! /usr/bin/env python3
import rospy
import actionlib
import actClientClass.actFibonacciClient as actFibonacci
import actClientClass.actCalcMeanStdClient as actCalcMeanStd

def MainActClientCalcMeanStd():
  actTest = actCalcMeanStd.ActClientAveraging()
  actTest.goalParam = rospy.get_param("/calc_mean_std_sample")
  actClient = actTest.GenActionClientAveraging("/act_server_calc_mean_std", actTest.goalParam)
  print("ActionClient::CalcMeanStd..activated::samples:", actTest.goal.samples)  
  res = actTest.GenAveragingRes(actClient)
  print("Result:", res)

def	MainActClientFibonacci():
  actTest = actFibonacci.ActClientFibonacci()
  actTest.goalParam = rospy.get_param("/fibonacci_order")
  actClient = actTest.GenActionClientFibonacci("/act_server_fibonacci", actTest.goalParam)
  print("ActionClient::Fibonacci..activated::order:", actTest.goal.order)  
  res = actTest.GenFibonacciRes(actClient)
  print("Result:", ', '.join([str(n) for n in res.sequence]))

if __name__ == '__main__':
  try:
    rospy.init_node("ActionTestNode_Client", anonymous=True)
    MainActClientCalcMeanStd()
  except rospy.ROSInterruptException:
    pass