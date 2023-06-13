
#include "semaphore.h"
#include "log_define.h"
namespace gomros {
namespace common {

Semaphore::Semaphore(int value) : value(value) {}
Semaphore::~Semaphore() {}

void Semaphore::Wait() {
  std::unique_lock<std::mutex> lck(this->mtx);
  this->value--;
  if (this->value < 0) this->cond.wait(lck);
}

void Semaphore::Signal() {
  std::unique_lock<std::mutex> lck(this->mtx);
  this->value++;

  if (this->value <= 0) this->cond.notify_one();
}

bool Semaphore::TimeWait(std::chrono::milliseconds timeout) {
  std::unique_lock<std::mutex> lck(this->mtx);
  this->value--;
  if (this->value < 0) {
    std::cv_status ret = this->cond.wait_for(lck, timeout);
    // 超时
    warning_log("ret = %d ms = %d \n", (int)ret, (int)timeout.count());
    if (ret == std::cv_status::timeout) {
      this->value++;
      error_log(" timeout exit . \n ");
      return false;
    }
  }

  return true;
}

}  // namespace common
}  // namespace gomros
