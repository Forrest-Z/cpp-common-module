
#pragma once

#include "thread_pool/base_thread.h"

namespace gomros {
namespace common {

/**
 * @brief 队列任务处理线程
 * 
 */
class QueueThread : public BaseThread {
 public:
  QueueThread(const std::string& name, const ThreadPriority& priority,
              std::shared_ptr<Semaphore> exit_sema, VoidFunc task_func);
  ~QueueThread();

  virtual void NotifyStop();

  /**
   * @brief 通知线程执行处理任务；
   * task_empty为true时，说明当前没有任务，线程停止运行；
   * task_empty为false时，说明当前存在任务，线程运行，直到外部将task_empty设为true；
   *
   * @param task_empty 当前任务状态
   */
  void NotifyRun(bool task_empty);

 private:
  VoidFunc task_func;

  virtual void Exec();
};

}  // namespace common
}  // namespace gomros
