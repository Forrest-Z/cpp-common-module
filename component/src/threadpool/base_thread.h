
#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "log/log.h"
#include "thread_priority.h"
#include "threadpool/semaphore.h"

namespace gomros {
namespace threadpool {

typedef std::function<void()> VoidFunc;

/**
 * @brief
 * 线程退出信号，以共享形式给每个线程，最后一个线程退出时，会析构ExitSemaTrigger并发出信号
 *
 */
class ExitSemaTrigger {
 public:
  ExitSemaTrigger(std::shared_ptr<Semaphore> exit_sema_trigger)
      : exit_sema_trigger(exit_sema_trigger) {}
  ~ExitSemaTrigger() { exit_sema_trigger->Signal(); }

 private:
  std::shared_ptr<Semaphore> exit_sema_trigger;
};

/**
 * @brief 线程基类
 *
 */
class BaseThread {
 public:
  BaseThread(const std::string& name, const ThreadPriority& priority,
             std::shared_ptr<ExitSemaTrigger> exit_sema_trigger);
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
  std::shared_ptr<ExitSemaTrigger>
      exit_sema_trigger;  // 用于结束时通知外面主线程

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

}  // namespace threadpool
}  // namespace gomros
