
#include "basethread.h"

#include <math.h>
#include <pthread.h>
#include <algorithm>
#include <condition_variable>

namespace common {

basethread::basethread(const std::string& name, const ThreadPriority& priority)
    : name(name), priority(priority) {}

void basethread::setpriority() {
  pthread_t this_thread = this->thr.native_handle();

  const auto scheduling_type = SCHED_OTHER;
  int max_prio = sched_get_priority_max(scheduling_type);
  int min_prio = sched_get_priority_min(scheduling_type);
  uint32_t level = std::max((uint32_t) this->priority + 1, 4U);

  struct sched_param params;
  if (max_prio > min_prio) {
    params.sched_priority = min_prio + ((max_prio - min_prio) * level) / 4;
  } else {
    params.sched_priority = min_prio - ((min_prio - max_prio) * level) / 4;
  }

  pthread_setschedparam(this_thread, scheduling_type, &params);
}

void basethread::start() {
  this->thr = std::thread(std::bind(&basethread::run, this));
  this->setpriority();
}

void basethread::run() { this->exec(); }

basethread::~basethread() { this->thr.join(); }
}  // namespace common