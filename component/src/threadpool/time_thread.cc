
#include "time_thread.h"
#include "common/time_utils.h"

namespace gomros {
namespace threadpool {

constexpr const int DEFAULT_WAIT_TIME_us = 10 * 1000;

TimeThread::TimeThread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<ExitSemaTrigger> exit_sema_trigger)
    : BaseThread(name, priority, exit_sema_trigger) {}

TimeThread::~TimeThread() {}

void TimeThread::NotifyStop() {}

bool TimeThread::Compare(TaskItemType& a, TaskItemType& b) {
  return a.interval_ms < b.interval_ms;
}

void TimeThread::AddToTaskListAndSort(const TaskItemType& item) {
  TaskItemType new_item = item;
  std::lock_guard<std::mutex> lck(this->task_list_mtx);
  this->task_list.push_back(new_item);
  //  对 task_list 按时间点升序进行排序，时间点最近在前面
  this->task_list.sort(Compare);
}

void TimeThread::AddTask(const std::string& name, bool loopflag,
                         int interval_ms, VoidFunc task_func) {
  if (interval_ms <= 0) {
    LOG_ERROR("interval_ms is wrong , interval_ms =%d \n", interval_ms);
    return;
  }

  // 任务加入等待队列
  TaskItemType new_item = {common::TimeUtils::GetTimestamp_us() + interval_ms,
                           name, loopflag, interval_ms, task_func};
  this->AddToTaskListAndSort(new_item);
  this->cond.notify_one();  // notify_once if task_list changed by new task
}

void TimeThread::Exec() {
  while (is_alive) {
    TaskItemType task;
    // wait and get task
    {
      std::unique_lock<std::mutex> lck(this->task_list_mtx);

      int wait_time_us = DEFAULT_WAIT_TIME_us;

      if (this->task_list.size() > 0) {
        wait_time_us = this->task_list.front().time_point -
                       common::TimeUtils::GetTimestamp_us();

        if (wait_time_us < 0) {  // keep wait time >=0
          wait_time_us = 0;
        }
      }

      const std::cv_status ret =
          this->cond.wait_for(lck, std::chrono::milliseconds(wait_time_us));
      if (ret != std::cv_status::timeout) {
        continue;  // no timeout, 
      } else {     // timeout
        task = this->task_list.front();
        this->task_list.pop_front();
      }
    }

    // run task
    task.task_func();

    // re-add task if loop
    if (task.loopflag) {
      task.time_point += task.interval_ms * 1000;
      this->AddToTaskListAndSort(task);
    }
  }
}

}  // namespace threadpool
}  // namespace gomros
