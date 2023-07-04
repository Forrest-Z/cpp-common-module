
#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include "base_thread.h"

namespace gomros {
namespace threadpool {

/**
 * @brief 线程管理单例类
 *
 */
class ThreadManager {
 public:
  static ThreadManager* Instance();

  void AddTask(const std::string& name, bool loop_flag, int interval_ms,
               VoidFunc func);

  VoidFunc AddTask(const std::string& name, VoidFunc func, int priority);

  void AddTask(const std::string& name, VoidFunc loop_func, VoidFunc break_func,
               int priority);

  void StartAll();
  void StopAll(int timeout_ms);

 private:
  ThreadManager();

  static ThreadManager* instance;
  static std::mutex mtx;
  std::vector<BaseThread*> thread_pool;  // 首位 放time_thead
  std::shared_ptr<Semaphore> exit_sema;
  std::shared_ptr<ExitSemaTrigger> exit_sema_trigger;

  typedef enum ThreadManagerStatus {
    NOT_INIT = -1,
    INIT = 0,
    RUNNING,
    STOPING,
    STOPED
  } ThreadManagerStatus;

  ThreadManagerStatus status = NOT_INIT;
};

}  // namespace threadpool
}  // namespace gomros
