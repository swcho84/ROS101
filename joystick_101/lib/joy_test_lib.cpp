#include "joy_test_lib.h"

using namespace std;
using namespace ros;

JoyTest::JoyTest(const ConfigParam& cfg)
  : cfgParam_(cfg), joyXbox360_(cfg), joyPs4Bt_(cfg), joyPs3Bt_(cfg), joyLogiExtream_(cfg)
{
}

JoyTest::~JoyTest()
{
}

// main loop
void JoyTest::MainLoop()
{
  joyXbox360_.GenJoyInfoLoop();
  return;
}