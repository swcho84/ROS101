#!/usr/bin/env python3
import rospy
import srvServerClass.srvAddTwoIntsServer as srvAddTwoInts
import srvServerClass.srvSetMissionInfoServer as srvSetMission

def MainSrvServerSetMissionInfo():
  srvTest = srvSetMission.SrvServerSetMissionInfo()
  rospy.set_param("/mission_num", 0)
  rospy.set_param("/mission_end", False)
  srvServer = srvTest.ServerSetMissionInfo("/srv_server_set_mission_info")

def MainSrvServerAddTwoInts():
  srvTest = srvAddTwoInts.SrvServerAddTwoInt()
  rospy.set_param("/x_int", 3)
  rospy.set_param("/y_int", 4)
  rospy.set_param("/add_int_end", False)  
  srvServer = srvTest.ServerAddTwoInts("/srv_server_add_two_ints")

if __name__ == '__main__':
	try:
		rospy.init_node("ServiceTestNode_Server", anonymous=True)
		MainSrvServerSetMissionInfo()
		rospy.spin()		
	except rospy.ROSInterruptException:
		pass
