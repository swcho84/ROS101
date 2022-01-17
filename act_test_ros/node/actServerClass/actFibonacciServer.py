	#! /usr/bin/env python3
import rospy
import actionlib
from custom_msg_srv_param_ros.msg import FibonacciFeedback, FibonacciResult, FibonacciAction

class ActServerFibonacci(): 
  def __init__(self):
    self.feedback = FibonacciFeedback()
    self.result = FibonacciResult()

  def GenActionServerFibonacci(self, strActNm):
    self.actServer = actionlib.SimpleActionServer(strActNm, FibonacciAction, self.CbGoalLoop, False)
    self.actServer.start()

  def CbGoalLoop(self, goal):
    rate = rospy.Rate(1)
    success = True
    self.feedback.sequence = []
    self.feedback.sequence.append(0)
    self.feedback.sequence.append(1)

    rospy.loginfo("fibonacciAction: Executing, creating fibonacci sequence of order %i with seeds %i, %i"
                  % (goal.order, self.feedback.sequence[0], self.feedback.sequence[1]))

    for i in range(0, goal.order):
      if self.actServer.is_preempt_requested():
        rospy.loginfo("The goal has been cancelled/preempted")
        self.actServer.set_preempted()
        success = False
        break

      self.feedback.sequence.append(self.feedback.sequence[i + 1] + self.feedback.sequence[i])
      self.actServer.publish_feedback(self.feedback)
      rate.sleep()

    if success:
      self.result.sequence = self.feedback.sequence
      rospy.loginfo("Succeeded calculating the Fibonacci of order %i" % goal.order)
      self.actServer.set_succeeded(self.result)