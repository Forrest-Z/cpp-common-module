
#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include "base_thread.h"
#include "threadpool/thread_manager_interface.h"

namespace gomros {
namespace threadpool {

/**
 * @brief 线程管理单例类
 *
 */
class ThreadManager : public ThreadManagerInterface {
 public:
  static ThreadManager* Instance();

  static void AddTask(const std::string& name, bool loop_flag, int interval_ms,
                      VoidFunc func);

  static VoidFunc AddTask(const std::string& name, VoidFunc func, int priority);

  static void AddTask(const std::string& name, VoidFunc loop_func,
                      VoidFunc break_func, int priority);

  static void StartAll();
  static void StopAll(int timeout_ms);

 private:
  static ThreadManager* instance;
  static std::mutex mtx;
  static std::vector<BaseThread> thread_pool;  // 首位 放time_thead
  static std::shared_ptr<Semaphore> exit_sema;
  static std::shared_ptr<ExitSemaTrigger> exit_sema_trigger;

  typedef enum ThreadManagerStatus {
    NOT_INIT = -1,
    INIT = 0,
    RUNNING,
    STOPING,
    STOPED
  } ThreadManagerStatus;

  static ThreadManagerStatus status;
};

}  // namespace threadpool
}  // namespace gomros
