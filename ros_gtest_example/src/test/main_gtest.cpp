#include <gtest/gtest.h>
#include <ros/ros.h>

using namespace std;

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "ros_gtest_example_gtest_side");
  return RUN_ALL_TESTS();
}