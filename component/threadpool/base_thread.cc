
#include "base_thread.h"

#include <math.h>
#include <pthread.h>
#include <algorithm>
#include <condition_variable>

#include "../log_define.h"

namespace common {

BaseThread::BaseThread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<Semaphore> exit_sema)
    : name(name), priority(priority), exit_sema(exit_sema) {}

void BaseThread::SetPriority() {
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

  int old_sched_priority = params.sched_priority;
  pthread_getschedparam(this_thread, &scheduling_type, &params);

  if (old_sched_priority == params.sched_priority) {
    // 设置失败，或优先级不变
    warning_log("%s thread prio = %d \n", this->name.c_str(),
                params.sched_priority);
  }
}

void BaseThread::Start() {
  this->thr = std::thread(std::bind(&BaseThread::Run, this));
  this->SetPriority();
}

void BaseThread::Run() {
  this->Exec();
  warning_log("%s exec end . \n", this->name.c_str());
  this->exit_sema->Signal();
  warning_log("%s exit_sema signal . \n", this->name.c_str());
}

BaseThread::~BaseThread() { this->thr.detach(); }
}  // namespace common