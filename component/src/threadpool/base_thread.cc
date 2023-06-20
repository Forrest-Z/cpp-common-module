
#include "base_thread.h"

namespace gomros {
namespace threadpool {

BaseThread::BaseThread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<ExitSemaTrigger> exit_sema_trigger)
    : name(name), priority(priority), exit_sema_trigger(exit_sema_trigger) {}

void BaseThread::Start() {
  this->thr = std::thread(std::bind(&BaseThread::Run, this));
  LOG_INFO("%s started !!!!! \n", this->GetName().c_str());
}

void BaseThread::Run() {
  this->priority.SetPriority();

  this->Exec();
  this->exit_sema_trigger = nullptr;  // 退出时，释放 exit_sema_trigger
  LOG_INFO("%s exec end , and exit_sema_trigger signal . \n",
           this->name.c_str());
}

BaseThread::~BaseThread() { this->thr.detach(); }
}  // namespace threadpool
}  // namespace gomros
