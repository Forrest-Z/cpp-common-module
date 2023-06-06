
#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace common {

class semaphore {
 private:
  std::mutex mtx;
  std::condition_variable cond;
  int value;

 public:
  semaphore(int value);
  ~semaphore();

  void wait();
  void signal();

  /**
   * @brief 等待信号，并加上超时限制
   *
   * @param timeout 超时等待时间
   * @return true 正常等待退出
   * @return false 超时退出
   */
  bool time_wait(std::chrono::microseconds timeout);
};

}  // namespace common
