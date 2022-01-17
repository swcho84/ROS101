#! /usr/bin/env python3
import rospy
import actionlib
from custom_msg_srv_param_ros.msg import AveragingGoal, AveragingAction

class ActClientAveraging(): 
  def __init__(self):
    self.goalParam = 10

  def GenActionClientAveraging(self, strActNm, order):
    res = actionlib.SimpleActionClient(strActNm, AveragingAction)
    res.wait_for_server()
    self.goal = AveragingGoal(order)
    res.send_goal(self.goal)
    return res

  def GenAveragingRes(self, client):
    client.wait_for_result()
    return client.get_result()     