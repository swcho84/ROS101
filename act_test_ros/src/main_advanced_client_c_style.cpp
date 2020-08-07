#include <ros/ros.h>
#include <boost/thread.hpp>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <custom_msg_srv_param_ros/AveragingAction.h>

typedef actionlib::SimpleActionClient<custom_msg_srv_param_ros::AveragingAction> Client;

// Called once when the goal completes
void doneCb(const actionlib::SimpleClientGoalState& state,
            const custom_msg_srv_param_ros::AveragingResultConstPtr& result)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
  ROS_INFO("(mean,std_dev):(%.4f,%.4f)", result->mean, result->std_dev);
  ros::shutdown();
}

// Called once when the goal becomes active
void activeCb()
{
  ROS_INFO("Goal just went active");
}

// Called every time feedback is received for the goal
void feedbackCb(const custom_msg_srv_param_ros::AveragingFeedbackConstPtr& feedback)
{
  ROS_INFO("Got Feedback of length %d", feedback->sample);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "test_averaging");

  // create the action client
  Client ac("averaging", true);

  ROS_INFO("Waiting for action server to start.");
  ac.waitForServer();
  ROS_INFO("Action server started, sending goal.");

  // send a goal to the action
  custom_msg_srv_param_ros::AveragingGoal goal;
  goal.samples = 100;

  ROS_INFO("Averaging data: size(%d)", goal.samples);
  ac.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

  // wait for the action to return
  bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");

  ros::spin();

  // exit
  return 0;
}