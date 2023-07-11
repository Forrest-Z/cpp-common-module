
#include "thread_manager.h"
#include <gtest/gtest.h>

static bool running_flag = true;

static void AddNormalTask() {
  gomros::threadpool::VoidFunc loop_func = []() {
    while (running_flag) {
      sleep(1);
      printf("normal loop_func running . \n");
    }
    printf("normal loop_func exit . \n");
  };

  gomros::threadpool::VoidFunc break_func = []() {
    running_flag = false;
    printf("normal break_func exit . \n");
  };

  gomros::threadpool::ThreadManager::Instance().AddTask("normal", loop_func,
                                                        break_func);
}

static void AddQueueTask() {
  gomros::threadpool::VoidFunc task_func = []() {
    sleep(2);
    printf("queue task_func running . \n");
  };

  gomros::threadpool::VoidFunc ret_func;
  gomros::threadpool::ThreadManager::Instance().AddTask("queue_thread",
                                                        task_func, &ret_func);

  auto thread_func = [](gomros::threadpool::VoidFunc notify_func) {
    int count = 6;
    while (count--) {
      notify_func();
      sleep(1);
    }
  };

  auto t = new std::thread(thread_func, ret_func);
  t->detach();
}

static void AddTimeTask() {
  gomros::threadpool::VoidFunc task_func0 = []() {
    printf("task_func0 running . \n");
  };
  gomros::threadpool::VoidFunc task_func1 = []() {
    printf("task_func1 running . \n");
  };

  gomros::threadpool::ThreadManager::Instance().AddTimerTask(
      "task0", false, false, 500, task_func0);
  gomros::threadpool::ThreadManager::Instance().AddTimerTask(
      "task1", true, false, 900, task_func1);
}

TEST(threadpool, thread_manager) {
  gomros::threadpool::ThreadManagerConfig cfg;
  gomros::threadpool::ThreadManager::Instance().Init(cfg);
  AddNormalTask();
  AddTimeTask();

  gomros::threadpool::ThreadManager::Instance().StartAll();
  sleep(2);
  {  // time task
    gomros::threadpool::VoidFunc task_func2 = []() {
      printf("task_func2 running . \n");
    };
    gomros::threadpool::ThreadManager::Instance().AddTimerTask(
        "task2", true, false, 2000, task_func2);
  }
  AddQueueTask();

  sleep(5);
  gomros::threadpool::ThreadManager::Instance().DeleteTimerTask("task2");

  sleep(20);

  gomros::threadpool::ThreadManager::Instance().StopAll(3000);
  printf("wait thread manager exit . \n");
}
