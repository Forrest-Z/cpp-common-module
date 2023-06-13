
#pragma once

#include <thread>

namespace gomros {
namespace common {

/**
 * @brief 线程优先级类
 *
 */
class ThreadPriority {
 public:
  ThreadPriority(int priority, int max = -20, int min = 0,
                 int scheduling_type = SCHED_OTHER);
  ~ThreadPriority();

  /**
   * @brief 设置当前线程优先级
   *
   * @return true 成功
   * @return false 失败
   */
  bool SetPriority();

 public:
  int max;
  int min;
  int priority;
  int scheduling_type;
};

}  // namespace common
}  // namespace gomros
