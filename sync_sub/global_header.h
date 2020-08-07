#ifndef CAMIMG_LOGGER_GLOBAL_HEADER_H
#define CAMIMG_LOGGER_GLOBAL_HEADER_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <vector>
#include <dirent.h>
#include <fstream>

// for using folder generation
#include <sys/stat.h>
#include <sys/types.h>

// for using eigen library
#include <eigen3/Eigen/Dense>

// for using boost asio library
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/local_time/local_time_io.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/filesystem.hpp>

// essential header for ROS operation
#include <ros/ros.h>
#include <ros/serialization.h>

// using serial library
#include <serial/serial.h>

// for using OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

// for publishing and subscribing to images in ROS
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Imu.h>

// for subscribing multiple topic with the syncronizer
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

// for using standard messages, float 64 type
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Byte.h>

#define MAINCOM 0
#define EMBEDDED 1

#define PI 3.141592
#define R2D 180.0 / PI
#define D2R PI / 180.0

#endif