
#include "base_thread.h"

#include <math.h>
#include <pthread.h>
#include <algorithm>
#include <condition_variable>

#include <pthread.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>

#include "../log_define.h"

namespace common {

BaseThread::BaseThread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<Semaphore> exit_sema)
    : name(name), priority(priority), exit_sema(exit_sema) {}

void BaseThread::SetPriority() {
  pid_t this_pid = getpid();

  struct sched_param params;
  params.__sched_priority = priority.priority;

  warning_log("max_prio= %d , min_prio = %d , set_prio = %d \n", priority.max,
              priority.min, params.sched_priority);

  int ret;
  if (priority.scheduling_type == SCHED_OTHER) {
    ret = setpriority(PRIO_PROCESS, this_pid, priority.priority);
  } else {
    ret = pthread_setschedparam(this_pid, priority.scheduling_type, &params);
  }

  if (ret == -1) {
    error_log("%s set priority fail . \n", this->name.c_str());
  }
}

void BaseThread::Start() {
  this->thr = std::thread(std::bind(&BaseThread::Run, this));
}

void BaseThread::Run() {
  this->SetPriority();

  this->Exec();
  warning_log("%s exec end . \n", this->name.c_str());
  this->exit_sema->Signal();
  warning_log("%s exit_sema signal . \n", this->name.c_str());
}

BaseThread::~BaseThread() { this->thr.detach(); }
}  // namespace common