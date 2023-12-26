
#include <gtest/gtest.h>

#include <boost/timer/timer.hpp>

TEST(boost, timer) {
  boost::timer::auto_cpu_timer timer;

  // 在这里放置你想要测试执行时间的代码
  int len = 50000;
  int a;
  for (int i = 0; i < len; ++i) {
    for (int j = 0; j < len; ++j) {
      a = i * i + j * j;
    }
  }
}