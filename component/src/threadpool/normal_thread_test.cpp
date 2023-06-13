
#include "thread_pool/normal_thread.h"
#include <gtest/gtest.h>

static bool running_flag = true;

TEST(common, component_normal_thread) {
  auto exit_sema = std::make_shared<gomros::common::Semaphore>(0);

  gomros::common::VoidFunc loop_func = []() {
    while (running_flag) {
      sleep(1);
      printf("loop_func running . \n");
    }

    printf("loop_func exit . \n");

  };

  gomros::common::VoidFunc break_func = []() {
    running_flag = false;
    printf("break_func exit . \n");

  };

  auto t = std::make_shared<gomros::common::NormalThread>(
      "test_thread", gomros::common::ThreadPriority(-5), exit_sema, loop_func,
      break_func);

  t->Start();

  sleep(120);

  t->NotifyStop();

  printf("wait thread exit . \n");
  exit_sema->Wait();
}
