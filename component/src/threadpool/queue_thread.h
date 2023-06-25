
#pragma once

#include <atomic>

#include "base_thread.h"

namespace gomros {
namespace threadpool {

/**
 * @brief 队列任务处理线程
 *
 */
class QueueThread : public BaseThread {
 public:
  QueueThread(const std::string& name, const ThreadPriority& priority,
              std::shared_ptr<ExitSemaTrigger> exit_sema_trigger,
              VoidFunc task_func);
  ~QueueThread();

  virtual void NotifyStop();

  /**
   * @brief 通知线程执行处理任务；
   */
  void NotifyRun();

 private:
  VoidFunc task_func;
  bool is_alive = true;
  Semaphore exec_sema = Semaphore(0);
  virtual void Exec();
};

}  // namespace threadpool
}  // namespace gomros
