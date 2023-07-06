
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
   * @brief 初始化线程池配置
   *
   * @param config 配置
   */
  static void InitConfig(const ThreadManagerConfig& config);
  /**
   * @brief 实例化threadmanager
   *
   * @return ThreadManager* 返回 threadmanager 单例指针
   */
  static ThreadManager* Instance();
  /**
   * @brief destroy ThreadManager
   *
   */
  static void Destroy();

  /**
   * @brief 添加定时器任务，如果存在重名任务，会添加失败
   *
   * @param name
   * @param loop_flag
   * @param interval_ms
   * @param func
   * @return true
   * @return false
   */
  bool AddTimerTask(const std::string& name, bool loop_flag, int interval_ms,
                    VoidFunc func,bool execute_immediately);
  /**
   * @brief 从定时器中删除名称为name的task
   *
   * @param name
   */
  void DeleteTimerTask(const std::string& name);

  VoidFunc AddTask(const std::string& name, VoidFunc func);

  void AddTask(const std::string& name, VoidFunc loop_func,
               VoidFunc break_func);

  void StartAll();
  void StopAll(int timeout_ms);

 private:
  ThreadManager();

  ThreadPriority GetPriority(const std::string& thread_name);

  static ThreadManager* instance;
  static std::mutex mtx;
  static ThreadManagerConfig* cfg;

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
