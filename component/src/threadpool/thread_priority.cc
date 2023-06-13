

#include "thread_pool/thread_priority.h"

#include <math.h>
#include <algorithm>
#include <condition_variable>
#include <thread>

#include <pthread.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

namespace gomros {
namespace common {

ThreadPriority::ThreadPriority(int priority, int max, int min,
                               int scheduling_type)
    : priority(priority),
      max(max),
      min(min),
      scheduling_type(scheduling_type) {}
ThreadPriority::~ThreadPriority() {}

bool ThreadPriority::SetPriority() {
  pid_t this_pid = getpid();

  struct sched_param params;
  params.__sched_priority = this->priority;

  int ret;
  if (this->scheduling_type == SCHED_OTHER) {
    ret = setpriority(PRIO_PROCESS, this_pid, this->priority);
  } else {
    // 先修改调度算法
    ret = pthread_setschedparam(this_pid, this->scheduling_type, &params);
    ret &= setpriority(PRIO_PROCESS, this_pid, this->priority);
  }

  if (ret == -1) {
    return false;
  }
  return true;
}

}  // namespace common
}  // namespace gomros
