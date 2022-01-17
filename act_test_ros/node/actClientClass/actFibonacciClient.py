#! /usr/bin/env python3
import rospy
import actionlib
from custom_msg_srv_param_ros.msg import FibonacciGoal, FibonacciAction

class ActClientFibonacci(): 
  def __init__(self):
    self.goalParam = 10

  def GenActionClientFibonacci(self, strActNm, order):
    res = actionlib.SimpleActionClient(strActNm, FibonacciAction)
    res.wait_for_server()
    self.goal = FibonacciGoal(order)
    res.send_goal(self.goal)
    return res

  def GenFibonacciRes(self, client):
    client.wait_for_result()
    return client.get_result()     