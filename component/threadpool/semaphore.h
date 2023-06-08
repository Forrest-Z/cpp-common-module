
#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace common {

class Semaphore {
 private:
  std::mutex mtx;
  std::condition_variable cond;
  int value;

 public:
  Semaphore(int value);
  ~Semaphore();

  void Wait();
  void Signal();

  /**
   * @brief 等待信号，并加上超时限制,单位ms
   *
   * @param timeout 超时等待时间
   * @return true 正常等待退出
   * @return false 超时退出
   */
  bool TimeWait(std::chrono::milliseconds timeout);
};

}  // namespace common
