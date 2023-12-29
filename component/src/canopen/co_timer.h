

#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace canopen {

class CoTimer {
 private:
  struct Task {
    std::chrono::steady_clock::time_point time_point;
    std::string name;
    int interval_ms;
    std::function<void(void)> func;

    Task(const std::string& name, std::function<void(void)> func,
         uint32_t interval_ms = 100, int32_t cnt = -1)
        : name(name), func(func), interval_ms(interval_ms), cnt(cnt) {
      time_point = std::chrono::steady_clock::now();
      Inc();
    };

    bool Finished() { return (cnt == 0); }
    bool Forever() { return (cnt == -1); }

    void Inc() {
      time_point += std::chrono::milliseconds(interval_ms);
      if (cnt > 0) {
        --cnt;
      };
    }

    bool operator<(const Task& b) { return this->time_point < b.time_point; }

    bool operator==(const std::string& name) { return (this->name == name); }

   private:
    int cnt = -1;
  };

 public:
  CoTimer();
  ~CoTimer();

  bool AddTask(const std::string& name, std::function<void(void)> func,
               uint32_t interval_ms = 500, int32_t cnt = -1);

  std::string Debug();

 private:
  void Run();

  static bool Compare(std::shared_ptr<Task>& a, std::shared_ptr<Task>& b) {
    return a->time_point < b->time_point;
  }

 private:
  bool is_alive = true;
  std::thread thr;
  std::mutex mtx;
  std::condition_variable cv;

  std::list<std::shared_ptr<Task>> tasks;
};

}  // namespace canopen