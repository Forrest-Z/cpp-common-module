
#include "include/common/threadpool.h"
namespace common {

ThreadPool::ThreadPool(/* args */) {}

ThreadPool::~ThreadPool() {
  this->is_alive = false;

  for (auto& item : this->work_set_map) {
    item.second->worker.join();
  }
}

bool ThreadPool::AddNewWork(work_ptr item, std::string identifier) {
  std::lock_guard<std::mutex> lck(this->mtx);

  // 查询是否有workset ，没有的话就添加一个新的

  auto ret = this->work_set_map.find(identifier);

  if (ret == this->work_set_map.end()) {
    auto work_set = std::make_shared<WorkSetType>();
    std::thread t = std::thread(WorkProcess, this, work_set);
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
      work_ptr task;
      try {
        auto st = work_set->work_queue.wait_pull(task);
        if (st == boost::concurrent::queue_op_status::closed) {
          return;
        }
        task->run();
      } catch (boost::thread_interrupted&) {
        return;
      }
    } catch (...) {
      std::terminate();
      return;
    }
    /* code */
  }
}

}  // namespace common
