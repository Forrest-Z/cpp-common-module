
#include "base_thread.h"

namespace gomros {
namespace common {

BaseThread::BaseThread(const std::string& name, const ThreadPriority& priority,
                       std::shared_ptr<Semaphore> exit_sema)
    : name(name), priority(priority), exit_sema(exit_sema) {}

void BaseThread::Start() {
  this->thr = std::thread(std::bind(&BaseThread::Run, this));
}

void BaseThread::Run() {
  this->priority.SetPriority();

  this->Exec();
  LOG_WARNING("%s exec end , and exit_sema signal . \n", this->name.c_str());
  
  this->exit_sema->Signal();
}

BaseThread::~BaseThread() { this->thr.detach(); }
}  // namespace common
}  // namespace gomros
