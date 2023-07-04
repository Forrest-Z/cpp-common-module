
#include "time_thread.h"
#include "common/time_utils.h"

namespace gomros {
namespace threadpool {

constexpr const int DEFAULT_WAIT_TIME_us = 1000 * 1000;

TimeThread::TimeThread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<ExitSemaTrigger> exit_sema_trigger)
    : BaseThread(name, priority, exit_sema_trigger) {}

TimeThread::~TimeThread() {
  std::lock_guard<std::mutex> lck(this->task_list_mtx);
  for (auto& i : this->task_list) {
    delete i;
  }
  this->task_list.clear();
}

void TimeThread::NotifyStop() {
  this->is_alive = false;
  this->cond.notify_one();  // notify stop
}

void TimeThread::AddToTaskListAndSort(TaskItemType* item) {
  std::lock_guard<std::mutex> lck(this->task_list_mtx);
  this->task_list.push_back(item);
  //  对 task_list 按时间点升序进行排序，时间点最近在前面
  this->task_list.sort();
}

void TimeThread::DeleteTask(const std::string& name) {
  std::lock_guard<std::mutex> lck(this->task_list_mtx);
  for (auto i = task_list.begin(); i != task_list.end(); i++) {
    if ((*i)->name == name) {
      i = task_list.erase(i);
      LOG_INFO("delete timer task %s \n", name.c_str());
    }
  }
}

bool TimeThread::AddTask(const std::string& name, bool loopflag,
                         int interval_ms, VoidFunc task_func,
                         bool execute_immediately) {
  if (interval_ms < 0) {
    LOG_ERROR("interval_ms is wrong , interval_ms =%d \n", interval_ms);
    return false;
  }

  // check if have same task name
  {
    std::lock_guard<std::mutex> lck(this->task_list_mtx);
    for (auto i = task_list.begin(); i != task_list.end(); i++) {
      if ((*i)->name == name) {
        LOG_ERROR("task name repeated . name = %s \n", name.c_str());
        return false;
      }
    }
  }

  // 任务加入等待队列
  gomros::common::TimestampType init_interval_us =
      execute_immediately ? 0 : interval_ms * 1000;
  TaskItemType* new_item =
      new TaskItemType{common::TimeUtils::GetTimestamp_us() + init_interval_us,
                       name, loopflag, interval_ms, task_func};
  this->AddToTaskListAndSort(new_item);
  LOG_DEBUG("%s\n", this->DebugTaskList().c_str());
  this->cond.notify_one();  // notify_once if task_list changed by new task

  return true;
}

void TimeThread::Exec() {
  while (is_alive) {
    TaskItemType* task;
    std::cv_status cond_ret;
    // wait and get task
    {
      std::unique_lock<std::mutex> lck(this->task_list_mtx);

      int64_t wait_time_us = DEFAULT_WAIT_TIME_us;

      if (this->task_list.size() > 0) {
        wait_time_us = this->task_list.front()->time_point -
                       common::TimeUtils::GetTimestamp_us();
      }
      // LOG_DEBUG("wait_time_us = %ld \n", wait_time_us);

      if (wait_time_us > 0) {  // keep wait time >=0
        cond_ret =
            this->cond.wait_for(lck, std::chrono::microseconds(wait_time_us));
      }

      if (!this->is_alive) return;  // notify stop exit

      if (this->task_list.empty()) continue;  // 队列为空情况

      if (cond_ret != std::cv_status::timeout) {
        continue;  // no timeout,
      } else {     // timeout
        task = this->task_list.front();
        this->task_list.pop_front();
      }
    }  // ! wait and get task

    // run task
    task->task_func();

    // re-add task if loop
    if (task->loopflag) {
      task->time_point += task->interval_ms * 1000;
      this->AddToTaskListAndSort(task);
      task = nullptr;
      LOG_DEBUG("%s\n", this->DebugTaskList().c_str());
    } else {
      delete task;
      task = nullptr;
    }
  }  // ! while
}

std::string TimeThread::DebugTaskList() {
  char buf[UINT16_MAX];
  std::string ret;

  {
    std::unique_lock<std::mutex> lck(this->task_list_mtx);
    for (auto& i : this->task_list) {
      int len = snprintf(
          buf, sizeof(buf),
          "time_point = %ld, name =%s, loopflag = %d,interval_ms = %d \n ",
          i->time_point, i->name.c_str(), i->loopflag, i->interval_ms);
      ret += std::string(buf, len);
    }
  }

  return ret;
}

}  // namespace threadpool
}  // namespace gomros
