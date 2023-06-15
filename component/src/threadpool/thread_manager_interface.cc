
#include "thread_pool/thread_manager_interface.h"
#include "thread_pool/thread_manager.h"

#include <functional>
#include <string>

namespace gomros {
namespace common {

void ThreadManagerInterface::AddTask(const std::string& name, bool loop_flag,
                                     int interval_ms, VoidFunc func) {
  ThreadManager::Instance()->AddTask(name, loop_flag, interval_ms, func);
}

VoidFunc ThreadManagerInterface::AddTask(const std::string& name, VoidFunc func,
                                         int priority) {
  ThreadManager::Instance()->AddTask(name, func, priority);
}

void ThreadManagerInterface::AddTask(const std::string& name,
                                     VoidFunc loop_func, VoidFunc break_func,
                                     int priority) {
  ThreadManager::Instance()->AddTask(name, loop_func, break_func, priority);
}

}  // namespace common
}  // namespace gomros
