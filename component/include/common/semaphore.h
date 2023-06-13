
#pragma once

namespace gomros {
namespace common {
/**
 * @brief 信号量具体实现类，目前使用linux系统信号量实现
 * 
 */
class SemaphoreImpl;

/**
 * @brief 信号量
 * 
 */
class Semaphore {
 public:
  Semaphore(int value);
  ~Semaphore();

  /**
   * @brief 等待信号
   * 
   */
  void Wait();

  /**
   * @brief 发出信号
   * 
   */
  void Signal();

  /**
   * @brief 等待信号，并加上超时限制,单位ms
   *
   * @param timeout_ms 超时等待时间
   * @return true 正常等待退出
   * @return false 超时退出
   */
  bool TimeWait(int timeout_ms);

 private:
  SemaphoreImpl* impl;
};

}  // namespace common
}  // namespace gomros
