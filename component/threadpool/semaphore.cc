
#include "semaphore.h"
namespace common {

semaphore::semaphore(int value) : value(value) {}
semaphore::~semaphore() {}

void semaphore::wait() {
  std::unique_lock<std::mutex> lck(this->mtx);
  this->value--;
  if (this->value < 0) this->cond.wait(lck);
}

void semaphore::signal() {
  std::unique_lock<std::mutex> lck(this->mtx);
  this->value++;

  if (this->value <= 0) this->cond.notify_one();
}

bool semaphore::time_wait(std::chrono::microseconds ms) {
  std::unique_lock<std::mutex> lck(this->mtx);
  this->value--;
  if (this->value < 0) {
    std::cv_status ret = this->cond.wait_for(lck, ms);
    // 超时
    if (ret == std::cv_status::timeout) {
      this->value++;
      return false;
    }
  }

  return true;
}

}  // namespace common