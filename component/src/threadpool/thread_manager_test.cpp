
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

  gomros::threadpool::ThreadManager::Instance()->AddTask("normal", loop_func,
                                                         break_func);
}

static void AddQueueTask() {
  gomros::threadpool::VoidFunc task_func = []() {
    sleep(2);
    printf("queue task_func running . \n");
  };

  auto ret_func = gomros::threadpool::ThreadManager::Instance()->AddTask(
      "queue_thread", task_func);

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

  gomros::threadpool::ThreadManager::Instance()->AddTimerTask(
      "task0", false, 500, task_func0, false);
  gomros::threadpool::ThreadManager::Instance()->AddTimerTask(
      "task1", true, 900, task_func1, false);
}

TEST(threadpool, thread_manager) {
  AddNormalTask();
  AddTimeTask();

  gomros::threadpool::ThreadManager::Instance()->StartAll();
  sleep(2);
  {  // time task
    gomros::threadpool::VoidFunc task_func2 = []() {
      printf("task_func2 running . \n");
    };
    gomros::threadpool::ThreadManager::Instance()->AddTimerTask(
        "task2", true, 2000, task_func2, false);
    gomros::threadpool::ThreadManager::Instance()->AddTimerTask(
        "task3", true, 3000, task_func2, false);
    gomros::threadpool::ThreadManager::Instance()->AddTimerTask(
        "task4", true, 3500, task_func2, false);
  }
  AddQueueTask();

  sleep(30);

  gomros::threadpool::ThreadManager::Instance()->StopAll(3000);
  printf("wait thread manager exit . \n");
}
