
#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "common/semaphore.h"
#include "log/log.h"
#include "thread_priority.h"

namespace gomros {
namespace common {

typedef std::function<void()> VoidFunc;

class ExitSemaTriger
{
private:
  /* data */
public:
  ExitSemaTriger(/* args */);
  ~ExitSemaTriger();
};


/**
 * @brief 线程基类
 *
 */
class BaseThread {
 public:
  BaseThread(const std::string& name, const ThreadPriority& priority,
             std::shared_ptr<Semaphore> exit_sema);
  virtual ~BaseThread();

  /**
   * @brief 获取线程名称
   *
   * @return std::string 线程名称
   */
  std::string GetName() { return name; }

  /**
   * @brief 开起线程
   *
   */
  void Start();

  /**
   * @brief 通知线程结束，需要子类去实现
   *
   */
  virtual void NotifyStop() = 0;

 private:
  std::string name;
  ThreadPriority priority;
  std::thread thr;
  std::shared_ptr<Semaphore> exit_sema;  // 用于结束时通知外面主线程

  /**
   * @brief 线程主体程序，在开始时会设置优先级
   *
   */
  void Run();

  /**
   * @brief 任务逻辑程序，需要子类去实现
   *
   */
  virtual void Exec() = 0;
};

}  // namespace common
}  // namespace gomros
