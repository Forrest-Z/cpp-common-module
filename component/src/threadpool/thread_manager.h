
#pragma once

#include <functional>
#include <string>

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

  typedef enum ThreadManagerStatus {
    INIT = 0,
    RUNNING,
    STOPING,
    STOPED
  } ThreadManagerStatus;

  ThreadManagerStatus status = ThreadManagerStatus::INIT;
};

}  // namespace threadpool
}  // namespace gomros
