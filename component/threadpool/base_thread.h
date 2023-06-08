
#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "semaphore.h"

namespace common {

typedef std::function<void()> VoidFunc;

enum class ThreadPriority : uint32_t {
  Low = 0,
  Normal = 1,
  High = 2,
  VeryHigh = 3,
  Critical = 4,
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
  std::mutex mtx;
  std::string GetName() { return name; }
  ThreadPriority GetPriority() { return priority; }

  void Start();
  virtual void NotifyStop() = 0;
};

}  // namespace common
