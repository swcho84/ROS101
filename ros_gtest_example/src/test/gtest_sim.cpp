#include "gtest_sim.h"

TEST(GTestExample, CASE1) {
  auto arithOper = ArithmeticOper();
  ASSERT_EQ(7, arithOper.CalcAddNum(5, 2));
}

TEST(GTestExample, CASE2) {
  auto arithOper = ArithmeticOper();
  EXPECT_EQ(6, arithOper.CalcAddNum(3, 3));
  EXPECT_EQ(8, arithOper.CalcAddNum(3, 5));
}

TEST(GTestExample, CASE3) {
  auto arithOper = ArithmeticOper();
  ASSERT_EQ(0, arithOper.CalcSubNum(3, 3));
}