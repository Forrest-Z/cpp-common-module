
#pragma once

#include <string>

namespace gomros {
namespace async {
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
  /**
   * @brief 线程内信号量
   *
   * @param value 初值
   */
  Semaphore(int value);

  /**
   * @brief
   * 进程间信号量，不存在会创建，存在直接获取，其中只有创建时value才会起作用
   *
   * @param name 名称
   * @param value 初值
   */
  Semaphore(const std::string& name, int value);
  ~Semaphore();

  /**
   * @brief 等待信号
   *
   */
  void Wait();

  /**
   * @brief 发出信号
   *
   * @param limit 信号量value限制(value <= limit)，超出不发
   */
  void Signal(uint16_t limit = UINT16_MAX);

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

}  // namespace async
}  // namespace gomros
