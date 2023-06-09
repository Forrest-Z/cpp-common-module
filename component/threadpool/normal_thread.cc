
#include "normal_thread.h"
#include "log_define.h"

namespace common {

NormalThread::NormalThread(const std::string& name,
                           const ThreadPriority& priority,
                           std::shared_ptr<Semaphore> exit_sema,
                           VoidFunc loop_func, VoidFunc break_func)
    : BaseThread(name, priority, exit_sema),
      loop_func(loop_func),
      break_func(break_func) {}

NormalThread::~NormalThread() {}

void NormalThread::NotifyStop() {
  info_log("%s exect break_func . \n", this->GetName().c_str());
  break_func();
}
void NormalThread::Exec() {
  info_log("%s exec loop_func . \n", this->GetName().c_str());
  loop_func();
}
}  // namespace common