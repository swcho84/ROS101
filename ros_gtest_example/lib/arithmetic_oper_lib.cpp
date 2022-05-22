#include "arithmetic_oper_lib.h"

using namespace std;
using namespace ros;

using namespace ArithOper;

ArithmeticOper::ArithmeticOper() {}

ArithmeticOper::~ArithmeticOper() {}

int ArithmeticOper::CalcAddNum(const int nA, const int nB) { return nA + nB; }

int ArithmeticOper::CalcSubNum(const int nA, const int nB) { return nA - nB; }
