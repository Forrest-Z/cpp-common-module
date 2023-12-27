#include "co_timer.h"

#include <algorithm>

namespace canopen {
CoTimer::CoTimer() { this->thr = std::thread(&CoTimer::Run, this); }

CoTimer::~CoTimer() {
  is_alive = false;
  this->thr.join();
}

bool CoTimer::AddTask(const std::string& name, std::function<void(void)> func,
                      uint32_t interval_ms, int32_t cnt) {
  std::lock_guard<std::mutex> lck(mtx);

  for (auto& i : this->tasks) {
    if (*i == name) {
      return false;
    }
  }

  this->tasks.push_back(std::make_shared<Task>(name, func, interval_ms, cnt));
  this->tasks.sort();
  this->cv.notify_one();
  return true;
}
void CoTimer::Run() {
  while (is_alive) {
    std::unique_lock<std::mutex> lck(mtx);
    std::shared_ptr<Task> t;

    if (tasks.size() > 0) {
      auto ret = cv.wait_until(lck, tasks.front()->time_point);

      if (ret == std::cv_status::no_timeout) continue;

      t = tasks.front();
      tasks.pop_front();
      lck.unlock();

      // run
      t->func();

      // repeat
      lck.lock();
      t->Inc();
      if (!t->Finished()) {
        tasks.push_back(t);
        tasks.sort();
      }

    } else {
      cv.wait_for(lck, std::chrono::milliseconds(1000));
    }
  }
}
}  // namespace canopen