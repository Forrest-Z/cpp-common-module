
#include "include/common/threadpool.h"
namespace common {

ThreadPool::ThreadPool(/* args */) {}

ThreadPool::~ThreadPool() {
  this->is_alive = false;

  this->close();
  this->interrupt_and_join();
}

bool ThreadPool::AddNewWork(work_ptr item, std::string identifier) {
  std::lock_guard<std::mutex> lck(this->mtx);

  // 查询是否有workset ，没有的话就添加一个新的

  auto ret = this->work_set_map.find(identifier);

  if (ret == this->work_set_map.end()) {
    auto work_set = std::make_shared<WorkSetType>();
    boost::thread t = boost::thread(WorkProcess, this, work_set);
    work_set->worker = std::move(t);
    this->work_set_map.insert(
        std::pair<std::string, std::shared_ptr<WorkSetType>>(identifier,
                                                             work_set));

    ret = this->work_set_map.find(identifier);
    if (ret == this->work_set_map.end()) {
      return false;
    }
  }

  // add item
  { ret->second->work_queue.push(item); }

  return true;
}

void ThreadPool::WorkProcess(ThreadPool* tpool,
                             std::shared_ptr<WorkSetType> work_set) {
  while (tpool->is_alive) {
    try {
      try {
        work_ptr task;
        auto st = work_set->work_queue.wait_pull(task);
        if (st == boost::concurrent::queue_op_status::closed) {
          work_set->state = WorkSetState::EXIT;
          return;
        }
        work_set->state = WorkSetState::START_RUNNING;
        task->run();
        work_set->state = WorkSetState::STOP_RUNNING;
      } catch (boost::thread_interrupted&) {
        work_set->state = WorkSetState::EXIT;
        return;
      }
    } catch (...) {
      std::terminate();
      return;
    }
    /* code */
  }
}

bool ThreadPool::AllWorkFinished() {
  std::lock_guard<std::mutex> lck(this->mtx);

  for (auto& i : this->work_set_map) {
    if (!i.second->work_queue.empty()) {  // queue 不为空
      return false;
    }
    if (i.second->state == WorkSetState::START_RUNNING) {  // 正在执行任务
      return false;
    }
  }

  return true;
}

void ThreadPool::close() {
  for (auto& item : this->work_set_map) {
    item.second->work_queue.close();
  }
}
void ThreadPool::interrupt_and_join() {
  for (auto& item : this->work_set_map) {
    item.second->worker.interrupt();
    item.second->worker.join();
  }
}

}  // namespace common
