
#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "semaphore.h"

namespace common {

typedef std::function<void()> VoidFunc;

class ThreadPriority {
 public:
  int max;
  int min;
  int priority;
  int scheduling_type;

 public:
  ThreadPriority(int priority, int max = -20, int min = 0,
                 int scheduling_type = SCHED_OTHER)
      : priority(priority),
        max(max),
        min(min),
        scheduling_type(scheduling_type) {}
  ~ThreadPriority() {}
};

class BaseThread {
 private:
  std::string name;
  ThreadPriority priority;
  std::thread thr;
  std::shared_ptr<Semaphore> exit_sema;  // 用于结束时通知外面主线程

  void SetPriority();
  void Run();
  virtual void Exec() = 0;

 public:
  BaseThread(const std::string& name, const ThreadPriority& priority,
             std::shared_ptr<Semaphore> exit_sema);
  virtual ~BaseThread();

  std::string GetName() { return name; }
  ThreadPriority GetPriority() { return priority; }

  void Start();
  virtual void NotifyStop() = 0;
};

}  // namespace common
