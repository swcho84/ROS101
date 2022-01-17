#!/usr/bin/env python3
import rospy
import sys  # using terminal
import srvClientClass.srvAddTwoIntsClient as srvAddTwoInts
import srvClientClass.srvSetMissionInfoClient as srvSetMissionInfo

def MainSrvClientSetMissionInfo():
  rate = rospy.Rate(1)
  srvClient = srvSetMissionInfo.SrvClientSetMissionInfo()
  while True:
    rate.sleep()
    srvClient.missionNum = rospy.get_param("/mission_num")
    res = srvClient.ClientSetMissionInfo("/srv_server_set_mission_info", srvClient.missionNum)
    print("FromServer:set mission info(x_ref,y_ref,z_ref,yaw_ref,yaw_stat", 
					res.x_ref, res.y_ref, res.z_ref, res.yaw_ref, res.yaw_ref_type)

def MainSrvClientAddTwoInts():
  rate = rospy.Rate(1)
  srvClient = srvAddTwoInts.SrvClientAddTwoInt()
  type = (str)(sys.argv[1])
  if (type == "sys"):
    srvClient.x = (int)(sys.argv[2])
    srvClient.y = (int)(sys.argv[3])
    print("FromServer: %s + %s = %s" %
					(srvClient.x, srvClient.y,
						srvClient.ClientAddTwoInts("/srv_server_add_two_ints",
						srvClient.x, srvClient.y, type)))
  elif (type == "rosparam"):
    while True:
      rate.sleep() 
      if (rospy.has_param("/add_int_end") and (rospy.get_param("/add_int_end") == True)):
          print("End Client..wait::rosparam")
          continue      
      if ((rospy.has_param("/x_int")) and (rospy.has_param("/y_int"))):
        srvClient.x = rospy.get_param("/x_int")
        srvClient.y = rospy.get_param("/y_int")
        print("FromServer: %s + %s = %s"%
              (srvClient.x, srvClient.y, 
                srvClient.ClientAddTwoInts("/srv_server_add_two_ints",
                srvClient.x, srvClient.y, type)))
  else:
    srvClient.x = 1
    srvClient.y = 2
    print("FromServer: %s + %s = %s"%
					(srvClient.x, srvClient.y, 
						srvClient.ClientAddTwoInts("/srv_server_add_two_ints",
						srvClient.x, srvClient.y, type)))			

if __name__ == '__main__':
  try:
    rospy.init_node("ServiceTestNode_Client", anonymous=True)
    MainSrvClientSetMissionInfo()
    rospy.spin()		
  except rospy.ROSInterruptException:
    pass
