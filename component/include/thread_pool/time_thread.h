
#pragma once

#include "thread_pool/base_thread.h"

namespace gomros {
namespace common {

/**
 * @brief
 * 定时任务处理线程，单个进程内只有一个定时任务处理线程即可，可以通过addtask，汇集所有定时请求，并统一处理
 *
 */
class TimeThread : public BaseThread {
 public:
  TimeThread(const std::string& name, const ThreadPriority& priority,
             std::shared_ptr<Semaphore> exit_sema);
  ~TimeThread();

  virtual void NotifyStop();

  /**
   * @brief 添加定时任务，第一次执行时间为 interval_ms 间隔后
   *
   * @param name 任务名称
   * @param loopflag 是否为循环任务，true:循环 ，false:一次
   * @param interval_ms 间隔时间
   * @param task_func 任务函数
   */
  void AddTask(const std::string& name, bool loopflag, int interval_ms,
               VoidFunc task_func) {
    // 任务加入等待队列
  }

 private:
  typedef struct TaskItemType {
  } TaskItemType;

  virtual void Exec();
};

}  // namespace common
}  // namespace gomros
