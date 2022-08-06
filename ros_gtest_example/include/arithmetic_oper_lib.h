#ifndef ARITHMETIC_OPER_LIB_H
#define ARITHMETIC_OPER_LIB_H

// using vector type data
#include <iostream>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <ctime>
#include <vector>

// essential header for ROS-OpenCV operation
#include <ros/ros.h>

using namespace std;
using namespace ros;

// wrap-up namespace, for using google test
namespace ArithOper
{
class ArithmeticOper
{
public:
  ArithmeticOper();
  ~ArithmeticOper();

	int CalcAddNum(const int nA, const int nB);
	int CalcSubNum(const int nA, const int nB);

private:

};
}

#endif  // ARITHMETIC_OPER_LIB_H
