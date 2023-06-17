
#include "time_thread.h"
#include <gtest/gtest.h>

TEST(threadpool, time_thread) {
  gomros::threadpool::VoidFunc task_func0 = []() {
    printf("task_func0 running . \n");
  };
  gomros::threadpool::VoidFunc task_func1 = []() {
    printf("task_func1 running . \n");
  };

  gomros::threadpool::VoidFunc task_func2 = []() {
    printf("task_func2 running . \n");
  };

  std::shared_ptr<gomros::threadpool::TimeThread> t;
  auto exit_sema = std::make_shared<gomros::threadpool::Semaphore>(0);
  {
    auto exit_sema_trigger =
        std::make_shared<gomros::threadpool::ExitSemaTrigger>(exit_sema);
    t = std::make_shared<gomros::threadpool::TimeThread>(
        "test_thread", gomros::threadpool::ThreadPriority(0),
        exit_sema_trigger);
  }

  t->AddTask("task0", false, 500, task_func0);
  t->AddTask("task1", true, 900, task_func1);
  t->AddTask("task2", true, 2000, task_func2);

  t->Start();

  sleep(10);

  printf("wait thread exit . \n");
  t->NotifyStop();

  printf("wait exit_sema . \n");
  exit_sema->Wait();
}
