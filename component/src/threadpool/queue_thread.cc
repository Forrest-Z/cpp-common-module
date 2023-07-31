
#include "queue_thread.h"

namespace gomros {
namespace threadpool {
QueueThread::QueueThread(const std::string& name,
                         const ThreadPriority& priority,
                         std::shared_ptr<ExitSemaTrigger> exit_sema_trigger,
                         VoidFunc task_func)
    : BaseThread(name, priority, exit_sema_trigger), task_func(task_func) {}
QueueThread::~QueueThread() {}

void QueueThread::NotifyStop() {
  is_alive = false;
  this->exec_sema.Signal();
  LOG_INFO("%s notify stop signal . \n", this->GetName().c_str());
}

void QueueThread::NotifyRun() {
  if (this->is_alive) {
    this->exec_sema.Signal(1);
  }
  LOG_DEBUG("%s notify run signal . \n", this->GetName().c_str());
}

void QueueThread::Exec() {
  while (this->is_alive) {
    this->exec_sema.Wait();

    if (!this->is_alive) {  // 当is_alive为false时，退出
      break;
    }

    this->task_func();
  }

  LOG_INFO("exec end .\n");
}
}  // namespace threadpool
}  // namespace gomros
