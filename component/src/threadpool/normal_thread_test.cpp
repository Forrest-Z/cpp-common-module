
#include "normal_thread.h"
#include <gtest/gtest.h>

static bool running_flag = true;

TEST(threadpool, component_normal_thread) {
  auto exit_sema = std::make_shared<gomros::threadpool::Semaphore>(0);

  gomros::threadpool::VoidFunc loop_func = []() {
    while (running_flag) {
      sleep(1);
      printf("loop_func running . \n");
    }

    printf("loop_func exit . \n");

  };

  gomros::threadpool::VoidFunc break_func = []() {
    running_flag = false;
    printf("break_func exit . \n");

  };

  auto t = std::make_shared<gomros::threadpool::NormalThread>(
      "test_thread", gomros::threadpool::ThreadPriority(-5), exit_sema, loop_func,
      break_func);

  t->Start();

  sleep(20);

  t->NotifyStop();

  printf("wait thread exit . \n");
  exit_sema->Wait();
}
