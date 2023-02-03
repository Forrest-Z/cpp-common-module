
#pragma once

#include <boost/thread/concurrent_queues/sync_queue.hpp>
#include <boost/thread/thread.hpp>

#include <map>
#include <memory>
#include <string>

namespace common {

class basic_work {
 public:
  virtual void run() = 0;
};

class threadpool {
 private:
 
  typedef std::map<std::string, boost::thread> thread_map;
  typedef std::shared_ptr<basic_work> work_ptr;

  thread_map threads;

  boost::concurrent::sync_queue<work_ptr> work_queue;

 public:
  threadpool(/* args */);
  ~threadpool();
};

threadpool::threadpool(/* args */) {}

threadpool::~threadpool() {}

}  // namespace common
