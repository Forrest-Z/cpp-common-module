
#pragma once

#include "base_thread.h"
#include "common/time_utils.h"

#include <condition_variable>
#include <list>
#include <map>
#include <mutex>

namespace gomros {
namespace threadpool {

/**
 * @brief
 * 定时任务处理线程，单个进程内只有一个定时任务处理线程即可，可以通过addtask，汇集所有定时请求，并统一处理
 *
 * 实现：采用系统启动时间，维护一个时间点升序的list,每个时间点带一个任务，
 * AddTask将任务插入list排序，线程找list头（时间点最近的）去等待执行，
 * 开始执行时判断是否是重复任务，如果是，计算该任务下一个时间点，并插入list中
 *
 */
class TimeThread : public BaseThread {
 public:
  TimeThread(const std::string& name, const ThreadPriority& priority,
             std::shared_ptr<ExitSemaTrigger> exit_sema_trigger);
  ~TimeThread();

  virtual void NotifyStop();

  /**
   * @brief 添加定时任务，第一次执行时间为 interval_ms 间隔后
   *
   * @param name 任务名称
   * @param loopflag 是否为循环任务，true:循环 ，false:一次
   * @param interval_ms 间隔时间，单位ms , 小于零会报错
   * @param task_func 任务函数
   * @param execute_immediately 是否立即执行（当在运行中），true:是
   * @return true 添加成功
   * @return false 添加失败
   */
  bool AddTask(const std::string& name, bool loopflag, int interval_ms,
               VoidFunc task_func, bool execute_immediately = true);

  void DeleteTask(const std::string& name);

 private:
  /**
   * @brief 任务结构数据定义
   *
   */
  typedef struct TaskItemType {
    common::TimestampType time_point;  // 任务执行时间点, 单位us
    std::string name;
    bool loopflag;
    int interval_ms;
    VoidFunc task_func;

    bool operator<(TaskItemType b) { return this->time_point < b.time_point; }
  } TaskItemType;

  std::list<TaskItemType> task_list;
  std::mutex task_list_mtx;
  std::condition_variable cond;

  void AddToTaskListAndSort(const TaskItemType& item);

  bool is_alive = true;

  virtual void Exec();

  /**
   * @brief 供内部debug调试使用，后期可以去掉
   *
   * @return std::string 调试信息
   */
  std::string DebugTaskList();
};

}  // namespace threadpool
}  // namespace gomros
