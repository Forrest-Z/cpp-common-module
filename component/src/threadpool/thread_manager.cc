
#include "threadpool/thread_manager.h"

namespace gomros {
namespace threadpool {

class ThreadManagerImpl {
 public:
  static void AddTask(const std::string& name, bool loop_flag, int interval_ms,
                      VoidFunc func) {}

  static VoidFunc AddTask(const std::string& name, VoidFunc func,
                          int priority) {}

  static void AddTask(const std::string& name, VoidFunc loop_func,
                      VoidFunc break_func, int priority) {}

  static void StarAll() {}
  static void StopAll() {}
};

// ThreadManager
ThreadManagerImpl* ThreadManager::impl = nullptr;
ThreadManager* ThreadManager::instance = nullptr;

ThreadManager* ThreadManager::Instance() {
  if (nullptr == impl) {
    impl = new ThreadManagerImpl();
    instance = new ThreadManager();
  }

  return instance;
}

void ThreadManager::AddTask(const std::string& name, bool loop_flag,
                            int interval_ms, VoidFunc func) {
  impl->AddTask(name, loop_flag, interval_ms, func);
}

VoidFunc ThreadManager::AddTask(const std::string& name, VoidFunc func,
                                int priority) {}

void ThreadManager::AddTask(const std::string& name, VoidFunc loop_func,
                            VoidFunc break_func, int priority) {}

void ThreadManager::StarAll() {}
void ThreadManager::StopAll(int timeout_ms) {}

}  // namespace threadpool
}  // namespace gomros
