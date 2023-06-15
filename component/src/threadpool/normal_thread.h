
#include "base_thread.h"

#pragma once
namespace gomros {
namespace threadpool {

/**
 * @brief 常规线程，线程循环和退出逻辑均由相关模块提供，用于支持特殊模块
 *
 */
class NormalThread : public BaseThread {
 public:
  NormalThread(const std::string& name, const ThreadPriority& priority,
               std::shared_ptr<Semaphore> exit_sema, VoidFunc loop_func,
               VoidFunc break_func);
  ~NormalThread();

  virtual void NotifyStop();

 private:
  VoidFunc loop_func;
  VoidFunc break_func;

  virtual void Exec();
};

}  // namespace threadpool
}  // namespace gomros
