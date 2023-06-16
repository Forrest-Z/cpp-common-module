
#include "queue_thread.h"
#include <gtest/gtest.h>

TEST(threadpool, queue_thread) {
  gomros::threadpool::VoidFunc task_func = []() {
    sleep(2);
    printf("task_func running . \n");
  };

  std::shared_ptr<gomros::threadpool::QueueThread> t;
  auto exit_sema = std::make_shared<gomros::threadpool::Semaphore>(0);
  {
    auto exit_sema_trigger =
        std::make_shared<gomros::threadpool::ExitSemaTrigger>(exit_sema);
    t = std::make_shared<gomros::threadpool::QueueThread>(
        "test_thread", gomros::threadpool::ThreadPriority(-5),
        exit_sema_trigger, task_func);
  }

  t->Start();

  int count = 10;
  while (count--) {
    t->NotifyRun();
    sleep(1);
  }

  printf("wait thread exit . \n");
  t->NotifyStop();

  printf("wait exit_sema . \n");
  exit_sema->Wait();
}
