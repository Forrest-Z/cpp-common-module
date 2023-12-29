
#include "co_timer.h"

#include <gtest/gtest.h>

TEST(co_timer, timer) {
  canopen::CoTimer timer;

  auto func1 = []() { printf("fun1 running\n"); };
  auto func2 = []() { printf("fun2 running\n"); };

  timer.AddTask("func1", func1, 1000, 10);
  timer.AddTask("func2", func2, 2000, 10);

  for (size_t i = 0; i < 10; i++) {
    sleep(3);
    std::cout << timer.Debug();
  }
}