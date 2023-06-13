
#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "common/semaphore.h"
#include "thread_pool/thread_priority.h"

namespace gomros {
namespace common {

typedef std::function<void()> VoidFunc;

class BaseThread {
 private:
  std::string name;
  ThreadPriority priority;
  std::thread thr;
  std::shared_ptr<Semaphore> exit_sema;  // 用于结束时通知外面主线程

  void Run();
  virtual void Exec() = 0;

 public:
  BaseThread(const std::string& name, const ThreadPriority& priority,
             std::shared_ptr<Semaphore> exit_sema);
  virtual ~BaseThread();

  std::string GetName() { return name; }

  void Start();
  virtual void NotifyStop() = 0;
};

}  // namespace common
}  // namespace gomros
