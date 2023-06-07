
#include "basethread.h"

#include <math.h>
#include <pthread.h>
#include <algorithm>
#include <condition_variable>

#include "../log_define.h"

namespace common {

basethread::basethread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<semaphore> exit_sema)
    : name(name), priority(priority), exit_sema(exit_sema) {}

void basethread::setpriority() {
  pthread_t this_thread = this->thr.native_handle();

  int scheduling_type = SCHED_OTHER;
  int max_prio = sched_get_priority_max(scheduling_type);
  int min_prio = sched_get_priority_min(scheduling_type);
  uint32_t level = std::max((uint32_t) this->priority + 1, 4U);

  struct sched_param params;
  if (max_prio > min_prio) {
    params.sched_priority = min_prio + ((max_prio - min_prio) * level) / 4;
  } else {
    params.sched_priority = min_prio - ((min_prio - max_prio) * level) / 4;
  }

  warning_log("max_prio= %d , min_prio = %d , set_prio = %d , level = %d \n",
              max_prio, min_prio, params.sched_priority, level);

  pthread_setschedparam(this_thread, scheduling_type, &params);

  pthread_getschedparam(this_thread, &scheduling_type, &params);
  warning_log("thread prio = %d \n", params.sched_priority);
}

void basethread::start() {
  this->thr = std::thread(std::bind(&basethread::run, this));
  this->setpriority();
}

void basethread::run() {
  this->exec();
  warning_log("exec end . \n");
  this->exit_sema->signal();
  warning_log("exit semaphore signal . \n");
}

basethread::~basethread() { this->thr.detach(); }
}  // namespace common