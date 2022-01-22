# joystick-101
ROS-based Joystick Command Generator

## Library Dependency and Prerequisites
- ros-noetic-joy (for using Xbox360 in ROS environment)
``` Bash
sudo apt-get install ros-noetic-joy
```
- virtual keyboard (for MoraiSimulator)
``` Bash
sudo apt-get install libxtst-dev
```
- mav_msg (for RotorS simulator)
```Bash
git clone https://github.com/ethz-asl/mav_comm
catkin build mav_comm  (at ~/catkin_ws/)
```
- vision_opencv (for using OpenCV4, check the noetic branch)
``` Bash
git clone https://github.com/ros-perception/vision_opencv
catkin build vision_opencv  (at ~/catkin_ws/)
```

## Installation
- using catkin build
``` Bash
catkin build (at ~/catkin_ws/)
```