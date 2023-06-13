
#pragma once

#include "thread_pool/base_thread.h"

namespace gomros {
namespace common {

class QueueThread : public BaseThread {
 private:
  VoidFunc task_func;

  virtual void Exec();

 public:
  QueueThread(const std::string& name, const ThreadPriority& priority,
              std::shared_ptr<Semaphore> exit_sema, VoidFunc task_func);
  ~QueueThread();

  virtual void NotifyStop();
};

}  // namespace common
}  // namespace gomros
