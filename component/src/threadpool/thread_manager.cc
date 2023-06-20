
#include "thread_manager.h"
#include "normal_thread.h"
#include "queue_thread.h"
#include "time_thread.h"

namespace gomros {
namespace threadpool {

ThreadManager* ThreadManager::instance = nullptr;
std::mutex ThreadManager::mtx;
std::vector<BaseThread*> ThreadManager::thread_pool;
ThreadManager::ThreadManagerStatus ThreadManager::status =
    ThreadManagerStatus::NOT_INIT;
std::shared_ptr<Semaphore> ThreadManager::exit_sema = nullptr;
std::shared_ptr<ExitSemaTrigger> ThreadManager::exit_sema_trigger = nullptr;

ThreadManager* ThreadManager::Instance() {
  std::lock_guard<std::mutex> lck(mtx);
  if (nullptr == instance) {
    instance = new ThreadManager();
    exit_sema = std::make_shared<Semaphore>(0);
    exit_sema_trigger = std::make_shared<ExitSemaTrigger>(exit_sema);
    thread_pool.push_back(new TimeThread(
        "time_thread", 0, exit_sema_trigger));  // creat time thread
    status = ThreadManagerStatus::INIT;
    LOG_INFO("thread manager creat instance . \n");
  }

  return instance;
}

void ThreadManager::AddTask(const std::string& name, bool loop_flag,
                            int interval_ms, VoidFunc func) {
  std::lock_guard<std::mutex> lck(mtx);
  switch (status) {
    case ThreadManagerStatus::INIT:
      dynamic_cast<TimeThread*>(thread_pool[0])
          ->AddTask(name, loop_flag, interval_ms, func);
      break;
    case ThreadManagerStatus::RUNNING:
      dynamic_cast<TimeThread*>(thread_pool[0])
          ->AddTask(name, loop_flag, interval_ms, func);
      break;
    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
      break;
  }
}

static void NotifyQueueThreadFunc(gomros::threadpool::QueueThread* q_thread) {
  q_thread->NotifyRun();
}

VoidFunc ThreadManager::AddTask(const std::string& name, VoidFunc func,
                                int priority) {
  std::lock_guard<std::mutex> lck(mtx);

  VoidFunc ret = [] {};

  switch (status) {
    case ThreadManagerStatus::INIT: {
      auto queue_thread = new QueueThread(name, ThreadPriority(priority),
                                          exit_sema_trigger, func);
      thread_pool.push_back(queue_thread);
      ret = std::bind(NotifyQueueThreadFunc, queue_thread);
    } break;
    case ThreadManagerStatus::RUNNING: {
      auto queue_thread = new QueueThread(name, ThreadPriority(priority),
                                          exit_sema_trigger, func);
      thread_pool.push_back(queue_thread);
      ret = std::bind(NotifyQueueThreadFunc, queue_thread);
      queue_thread->Start();  // start thread
    } break;
    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
      break;
  }
  return ret;
}

void ThreadManager::AddTask(const std::string& name, VoidFunc loop_func,
                            VoidFunc break_func, int priority) {
  std::lock_guard<std::mutex> lck(mtx);
  switch (status) {
    case ThreadManagerStatus::INIT: {
      auto normal_thread =
          new NormalThread(name, ThreadPriority(priority), exit_sema_trigger,
                           loop_func, break_func);
      thread_pool.push_back(normal_thread);
    } break;
    case ThreadManagerStatus::RUNNING: {
      auto normal_thread =
          new NormalThread(name, ThreadPriority(priority), exit_sema_trigger,
                           loop_func, break_func);
      thread_pool.push_back(normal_thread);
      normal_thread->Start();
    } break;
    default:
      LOG_INFO("wrong invoke , current status is %d \n", status);
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
        for (auto& t : thread_pool) {
          delete t;
        }
        thread_pool.clear();
      } else {
        LOG_INFO("thread pool timeout exit . \n");
      }

      status = ThreadManagerStatus::STOPED;

      break;
  }
}

}  // namespace threadpool
}  // namespace gomros
