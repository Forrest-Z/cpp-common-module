
#include "normal_thread.h"
#include <gtest/gtest.h>

static bool running_flag = true;

TEST(threadpool, component_normal_thread) {
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

  std::shared_ptr<gomros::threadpool::NormalThread> t;
  {
    auto exit_sema = std::make_shared<gomros::threadpool::Semaphore>(0);
    auto exit_sema_trigger =
        std::make_shared<gomros::threadpool::ExitSemaTrigger>(exit_sema);
    t = std::make_shared<gomros::threadpool::NormalThread>(
        "test_thread", gomros::threadpool::ThreadPriority(-5),
        exit_sema_trigger, loop_func, break_func);
  }

  t->Start();

  sleep(10);

  printf("wait thread exit . \n");
  t->NotifyStop();
}
