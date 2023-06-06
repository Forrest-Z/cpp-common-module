
#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "semaphore.h"

namespace common {

enum class ThreadPriority : uint32_t {
  Low = 0,
  Normal = 1,
  High = 2,
  VeryHigh = 3,
  Critical = 4,
};

class basethread {
 private:
  std::string name;
  ThreadPriority priority;
  std::thread thr;
  std::shared_ptr<semaphore> sema;  // 用于结束时通知外面主线程

  void setpriority();
  void run();

 public:
  basethread(const std::string& name, const ThreadPriority& priority);
  virtual ~basethread();
  std::mutex mtx;
  std::string getname() { return name; }
  ThreadPriority getpriority() { return priority; }

  void start();
  virtual void notifystop() = 0;
  virtual void exec() = 0;
};

}  // namespace common
