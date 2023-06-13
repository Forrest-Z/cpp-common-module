
#include "common/semaphore.h"

#include <semaphore.h>

namespace gomros {
namespace common {

class SemaphoreImpl {
 public:
  SemaphoreImpl(int value) : value(value) { sem_init(&sema, 0, value); }
  ~SemaphoreImpl() { sem_destroy(&sema); }

  void Wait() { sem_wait(&sema); }
  void Signal() { sem_post(&sema); }

  bool TimeWait(int timeout_ms) {
    timespec t;
    t.tv_sec = timeout_ms / 1000;
    t.tv_nsec = (timeout_ms % 1000) * 1000000;
    sem_timedwait(&sema, &t);
  }

 private:
  int value;
  sem_t sema;
};

// Semaphore

Semaphore::Semaphore(int value) { impl = new SemaphoreImpl(value); }

Semaphore::~Semaphore() { delete impl; }

void Semaphore::Wait() { impl->Wait(); }

void Semaphore::Signal() { impl->Signal(); }

bool Semaphore::TimeWait(int timeout_ms) { return impl->TimeWait(timeout_ms); }

}  // namespace common
}  // namespace gomros
