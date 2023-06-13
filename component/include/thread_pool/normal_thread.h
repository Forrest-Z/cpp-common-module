
#include "base_thread.h"

#pragma once
namespace gomros {
namespace common {

class NormalThread : public BaseThread {
 private:
  VoidFunc loop_func;
  VoidFunc break_func;

  virtual void Exec();

 public:
  NormalThread(const std::string& name, const ThreadPriority& priority,
               std::shared_ptr<Semaphore> exit_sema, VoidFunc loop_func,
               VoidFunc break_func);
  ~NormalThread();

  virtual void NotifyStop();
};

}  // namespace common
}  // namespace gomros

