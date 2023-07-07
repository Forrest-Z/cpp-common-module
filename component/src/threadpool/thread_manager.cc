
#include "thread_manager.h"
#include "normal_thread.h"
#include "queue_thread.h"
#include "time_thread.h"

namespace gomros {
namespace threadpool {

ThreadManager* ThreadManager::instance = nullptr;

void ThreadManager::Init(const ThreadManagerConfig& config) {
  cfg = config;
  LOG_INFO("config init success . \n");

  exit_sema = std::make_shared<Semaphore>(0);
  exit_sema_trigger = std::make_shared<ExitSemaTrigger>(exit_sema);
  thread_pool.push_back(new TimeThread(
      "time_thread", 0, exit_sema_trigger));  // creat time thread
  status = ThreadManagerStatus::INIT;
}

void ThreadManager::UnInit() {
  {
    delete instance;
    instance = nullptr;
    LOG_INFO("thread manager instance destroy . \n");
  }
}

ThreadPriority ThreadManager::GetPriority(const std::string& thread_name) {
  auto ret = cfg.priority_map.find(thread_name);
  if (ret != cfg.priority_map.end()) {
    return ret->second;
  } else {
    return ThreadPriority(0);
  }
}

ThreadManager* ThreadManager::Instance() {
  if (nullptr == instance) {
    instance = new ThreadManager();
    LOG_INFO("thread manager creat instance . \n");
  }

  return instance;
}

void ThreadManager::Delete(const std::string& thread_name) {
  std::lock_guard<std::mutex> lck(mtx);
  for (auto i = thread_pool.begin(); i != thread_pool.end(); i++) {
    if ((*i)->GetName() == thread_name) {
      auto p = *i;
      i = thread_pool.erase(i);
      LOG_INFO("delete thread_name = %s \n", thread_name.c_str());
      delete p;  // 删除对象
      return;
    }
  }
}

void ThreadManager::DeleteTimerTask(const std::string& name) {
  std::lock_guard<std::mutex> lck(mtx);
  dynamic_cast<TimeThread*>(thread_pool[0])->DeleteTask(name);
}

bool ThreadManager::AddTimerTask(const std::string& name, bool loop_flag,
                                 bool execute_immediately, int interval_ms,
                                 VoidFunc func) {
  std::lock_guard<std::mutex> lck(mtx);
  switch (status) {
    case ThreadManagerStatus::INIT:
      return dynamic_cast<TimeThread*>(thread_pool[0])
          ->AddTask(name, loop_flag, execute_immediately, interval_ms, func);
      break;
    case ThreadManagerStatus::RUNNING:
      return dynamic_cast<TimeThread*>(thread_pool[0])
          ->AddTask(name, loop_flag, execute_immediately, interval_ms, func);
      break;
    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
      return false;
      break;
  }
}

static void NotifyQueueThreadFunc(gomros::threadpool::QueueThread* q_thread) {
  q_thread->NotifyRun();
}

bool ThreadManager::AddTask(const std::string& name, VoidFunc func,
                            VoidFunc* notify_func) {
  std::lock_guard<std::mutex> lck(mtx);

  *notify_func = [] {};

  for (auto& i : thread_pool) {
    if (i->GetName() == name) {
      LOG_WARN(" name repeated . name = %s \n", name.c_str());
      return false;
    }
  }

  switch (status) {
    case ThreadManagerStatus::INIT: {
      auto queue_thread =
          new QueueThread(name, GetPriority(name), exit_sema_trigger, func);
      thread_pool.push_back(queue_thread);
      *notify_func = std::bind(NotifyQueueThreadFunc, queue_thread);
      return true;
    } break;
    case ThreadManagerStatus::RUNNING: {
      auto queue_thread =
          new QueueThread(name, GetPriority(name), exit_sema_trigger, func);
      thread_pool.push_back(queue_thread);
      *notify_func = std::bind(NotifyQueueThreadFunc, queue_thread);
      queue_thread->Start();  // start thread
      return true;
    } break;
    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
      return false;
      break;
  }
}

bool ThreadManager::AddTask(const std::string& name, VoidFunc loop_func,
                            VoidFunc break_func) {
  std::lock_guard<std::mutex> lck(mtx);
  for (auto& i : thread_pool) {
    if (i->GetName() == name) {
      LOG_WARN(" name repeated . name = %s \n", name.c_str());
      return false;
    }
  }

  switch (status) {
    case ThreadManagerStatus::INIT: {
      auto normal_thread = new NormalThread(
          name, GetPriority(name), exit_sema_trigger, loop_func, break_func);
      thread_pool.push_back(normal_thread);
      return true;
    } break;
    case ThreadManagerStatus::RUNNING: {
      auto normal_thread = new NormalThread(
          name, GetPriority(name), exit_sema_trigger, loop_func, break_func);
      thread_pool.push_back(normal_thread);
      normal_thread->Start();
      return true;
    } break;
    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
      return false;
      break;
  }
}

void ThreadManager::StartAll() {
  std::lock_guard<std::mutex> lck(mtx);

  auto s = status;

  switch (s) {
    case ThreadManagerStatus::INIT:
      for (auto& t : thread_pool) {
        t->Start();  // 启动线程
      }
      status = ThreadManagerStatus::RUNNING;
      break;

    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
      break;
  }
}
void ThreadManager::StopAll(int timeout_ms) {
  std::lock_guard<std::mutex> lck(mtx);
  switch (status) {
    case ThreadManagerStatus::STOPED:
      LOG_INFO("cur status is stoped . \n");
      break;
    default:
      status = ThreadManagerStatus::STOPING;

      // remove exit_sema_trigger from thread manager
      exit_sema_trigger = nullptr;

      for (auto& t : thread_pool) {
        t->NotifyStop();
      }

      // wait threads end
      int ret = exit_sema->TimeWait(timeout_ms);
      if (ret) {
        LOG_INFO("thread pool normal exit . \n");
      } else {
        LOG_INFO("thread pool timeout exit . \n");
      }

      // delete thread
      for (auto& t : thread_pool) {
        delete t;
      }
      thread_pool.clear();

      status = ThreadManagerStatus::STOPED;

      break;
  }
}

}  // namespace threadpool
}  // namespace gomros
