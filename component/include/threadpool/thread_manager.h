
#pragma once

#include <functional>
#include <string>

#include "thread_manager_interface.h"

namespace gomros {
namespace threadpool {

/**
 * @brief 线程管理类具体实现
 *
 */
class ThreadManagerImpl;

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

  static void StarAll();
  static void StopAll(int timeout_ms);

 private:
  static ThreadManagerImpl* impl;
  static ThreadManager* instance;
};

}  // namespace threadpool
}  // namespace gomros
