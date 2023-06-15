
#include "thread_manager.h"

namespace gomros {
namespace threadpool {

ThreadManager* ThreadManager::instance = nullptr;

ThreadManager* ThreadManager::Instance() {
  if (nullptr == instance) {
    instance = new ThreadManager();
  }

  return instance;
}

void ThreadManager::AddTask(const std::string& name, bool loop_flag,
                            int interval_ms, VoidFunc func) {}

VoidFunc ThreadManager::AddTask(const std::string& name, VoidFunc func,
                                int priority) {}

void ThreadManager::AddTask(const std::string& name, VoidFunc loop_func,
                            VoidFunc break_func, int priority) {}

void ThreadManager::StarAll() {}
void ThreadManager::StopAll(int timeout_ms) {}

}  // namespace threadpool
}  // namespace gomros
