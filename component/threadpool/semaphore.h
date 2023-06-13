/**
 * @file semaphore.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>

namespace gomros {
namespace common {

class Semaphore {
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

 private:
  std::mutex mtx;
  std::condition_variable cond;
  int value;
};

}  // namespace common
}  // namespace gomros

