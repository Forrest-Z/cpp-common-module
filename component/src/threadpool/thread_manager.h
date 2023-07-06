
#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "base_thread.h"

namespace gomros {
namespace threadpool {

/**
 * @brief 线程池配置数据
 *
 */
typedef struct ThreadManagerConfig {
  /**
   * @brief key 线程名 ； val 线程优先级
   *
   */
  std::map<std::string, ThreadPriority> priority_map;
  // ...
} ThreadManagerConfig;

/**
 * @brief 线程管理单例类
 *
 */
class ThreadManager {
 public:
  /**
  * @brief 实例化threadmanager
  *
  * @return ThreadManager* 返回 threadmanager 单例指针
  */
  static ThreadManager* Instance();
  /**
   * @brief 初始化线程池配置
   *
   * @param config 配置
   */
  void Init(const ThreadManagerConfig& config);
  /**
   * @brief destroy ThreadManager
   *
   */
  void UnInit();

  /**
   * @brief 添加定时任务
   *
   * @param name 任务名称
   * @param loop_flag 是否是循环任务 ， true:是
   * @param execute_immediately 是否立即执行 ，  true:是
   * @param interval_ms 时间间隔，等过interval_ms才开始执行
   * @param func 任务函数
   * @return true 添加成功
   * @return false 添加失败
   */
  bool AddTimerTask(const std::string& name, bool loop_flag,
                    bool execute_immediately, int interval_ms, VoidFunc func);
  /**
   * @brief 从定时器中删除名称为name的task
   *
   * @param name 任务名称
   */
  void DeleteTimerTask(const std::string& name);

  /**
   * @brief 添加队列任务，返回唤醒函数，通过唤醒函数控制队列任务执行
   *
   * @param name 任务名称，若重名会添加失败
   * @param func 执行函数
   * @param notify_func 返回唤醒函数,供外部使用
   * @return true 成功
   * @return false 失败
   */
  bool AddTask(const std::string& name, VoidFunc func,
                   VoidFunc* notify_func);

  /**
   * @brief
   * 无特定目的的普通线程，线程循环(loop_func)和退出逻辑(break_func)均由相关模块提供
   *
   * @param name 任务名称，若重名会添加失败
   * @param loop_func 循环函数
   * @param break_func 退出函数
     * @return true 成功
   * @return false 失败
   */
  bool AddTask(const std::string& name, VoidFunc loop_func,
               VoidFunc break_func);

  /**
   * @brief 删除列表里 名为thread_name的线程 （每个线程退出时，自行删除对象）
   *
   * @param thread_name 要删除的线程名
   */
  void Delete(const std::string& thread_name);

  /**
   * @brief 启动所有线程
   *
   */
  void StartAll();

  /**
   * @brief 停止所有线程
   *
   * @param timeout_ms 超时时间
   */
  void StopAll(int timeout_ms);

 private:
  ThreadPriority GetPriority(const std::string& thread_name);

  static ThreadManager* instance;
  std::mutex mtx;
  ThreadManagerConfig cfg;

  std::vector<BaseThread*> thread_pool;  // 首位 放time_thead
  std::shared_ptr<Semaphore> exit_sema;
  std::shared_ptr<ExitSemaTrigger> exit_sema_trigger;

  typedef enum ThreadManagerStatus {
    NOT_INIT = -1,
    INIT = 0,
    RUNNING,
    STOPING,
    STOPED
  } ThreadManagerStatus;

  ThreadManagerStatus status = NOT_INIT;
};

}  // namespace threadpool
}  // namespace gomros
