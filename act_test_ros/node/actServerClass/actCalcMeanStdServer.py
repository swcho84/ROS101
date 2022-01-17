	#! /usr/bin/env python3
import rospy
import actionlib
import numpy as np
from std_msgs.msg import Float32
from custom_msg_srv_param_ros.msg import AveragingGoal, AveragingFeedback, AveragingResult, AveragingAction

class ActServerAveraging(): 
  def __init__(self):
    self.feedback = AveragingFeedback()
    self.result = AveragingResult()
    self.dataCount = 0
    self.sum = 0.0
    self.sumSq = 0.0
    self.rate = rospy.Rate(1)
    self.threshold = 5.0
    self.rawData = 0.0

  def GenActionServerAveraging(self, strActNm, strTpNm):
    self.actServer = actionlib.SimpleActionServer(strActNm, AveragingAction, self.CbAnalysisLoop, False)
    self.sub = rospy.Subscriber(strTpNm, Float32, self.CbRawData)	
    self.actServer.start()

  def CbRawData(self, msg):
    self.rawData = msg.data

  def CbAnalysisLoop(self, goal):
    while True:
      self.dataCount += 1
      self.feedback.sample = self.dataCount
      self.feedback.data = self.rawData;    

      self.sum = self.sum + self.rawData
      self.feedback.mean = (self.sum) / (self.dataCount)
      self.sumSq = self.sumSq + np.power(self.rawData, 2)
      self.feedback.std_dev = np.sqrt(np.fabs((self.sumSq) / (self.dataCount)) - np.power(self.feedback.mean, 2))
      self.actServer.publish_feedback(self.feedback)

      self.result.mean = self.feedback.mean
      self.result.std_dev = self.feedback.std_dev
      goal = rospy.get_param("/calc_mean_std_sample")
      print("(goal,received):(", goal,  ", ", self.dataCount, ")")

      if (self.dataCount > goal):
        if (self.result.mean < self.threshold):
          print("Aborted(mean:", self.result.mean, "std_dev:", self.result.std_dev)
          self.actServer.set_aborted(self.result)
          self.dataCount = 0
          self.sum = 0.0
          self.sumSq = 0.0          
          break
        else:
          print("Succeed(mean:", self.result.mean, "std_dev:", self.result.std_dev)
          self.actServer.set_succeeded(self.result)
          self.dataCount = 0
          self.sum = 0.0
          self.sumSq = 0.0
          break
      self.rate.sleep()
