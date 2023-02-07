
#pragma once

#include <boost/thread/concurrent_queues/sync_queue.hpp>
#include <map>
#include <memory>
#include <string>
#include <thread>  //NOLINT

namespace common {

class basic_work {
 public:
  virtual void run() = 0;
};
typedef std::shared_ptr<basic_work> work_ptr;
typedef struct WorkSetType {
  std::mutex work_queue_mtx;
  // int max_queue_size = -1;
  std::thread worker;
  boost::concurrent::sync_queue<work_ptr> work_queue;
} WorkSetType;

class ThreadPool {
 public:
  ThreadPool(/* args */);
  ~ThreadPool();

  bool AddNewWork(work_ptr item, std::string identifier);
  // void SetWorkSetMaxSize(std::string identifier, int max_size);

 public:
  std::mutex mtx;
  bool is_alive = true;

 private:
  std::map<std::string, std::shared_ptr<WorkSetType>> work_set_map;

  static void WorkProcess(ThreadPool* tpool,
                          std::shared_ptr<WorkSetType> work_set);
};

}  // namespace common
