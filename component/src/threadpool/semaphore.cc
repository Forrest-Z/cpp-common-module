
#include "threadpool/semaphore.h"
#include "common/time_utils.h"

#include <chrono>
#include <thread>

#include <errno.h>
#include <fcntl.h> /* For O_* constants */
#include <semaphore.h>
#include <sys/stat.h> /* For mode constants */

namespace gomros {
namespace threadpool {

class SemaphoreImpl {
 public:
  SemaphoreImpl(int value) : value(value) {
    sem_init(&sema, 0, value);
    cur_sema = &sema;
  }

  SemaphoreImpl(const std::string& name, int value) {
    this->name = name;
    cur_sema = sem_open(name.c_str(), O_CREAT, O_CREAT | O_RDWR, value);
    this->is_ipc = true;
  }
  ~SemaphoreImpl() {
    if (is_ipc) {
      sem_close(cur_sema);
    } else
      sem_destroy(cur_sema);
  }

  void Wait() { sem_wait(cur_sema); }

  void Signal(uint16_t limit) {
    sem_getvalue(cur_sema, &value);

    if (value <= limit) {
      sem_post(cur_sema);
    }
  }

  bool TimeWait(int timeout_ms) {
    if (timeout_ms < 0) return false;

    timespec t;
    // 1970-01-01 00:00:00 +0000 (UTC)
    clock_gettime(CLOCK_REALTIME, &t);

    const long pow_10_3 = 1000;
    const long pow_10_6 = pow_10_3 * pow_10_3;
    const long pow_10_9 = pow_10_3 * pow_10_6;

    t.tv_sec += timeout_ms / pow_10_3;
    t.tv_nsec += (timeout_ms % pow_10_3) * pow_10_6 + t.tv_nsec / pow_10_9;
    t.tv_nsec %= pow_10_9;

    int ret = sem_timedwait(cur_sema, &t);

    // int err = errno;

    if (ret == 0)
      return true;
    else
      return false;
  }

  bool TimeWait_UseRelativeTime(int timeout_ms) {
    if (timeout_ms < 0) return false;

    common::TimestampType end_time =
        common::TimeUtils::GetTimestamp_us() + timeout_ms * 1000;

    while (common::TimeUtils::GetTimestamp_us() < end_time) {
      int ret = sem_trywait(cur_sema);
      if (ret == 0) {  // trywait 成功退出
        return true;
      }
      // sleep 1 ms
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return false;
  }

 private:
  int value;
  std::string name;
  sem_t sema;
  sem_t* cur_sema;
  bool is_ipc = false;  // 是否是进程间信号量，true:是
};

// Semaphore

Semaphore::Semaphore(int value) { impl = new SemaphoreImpl(value); }

Semaphore::Semaphore(const std::string& name, int value) {
  impl = new SemaphoreImpl(name, value);
}

Semaphore::~Semaphore() { delete impl; }

void Semaphore::Wait() { impl->Wait(); }

void Semaphore::Signal(uint16_t limit) { impl->Signal(limit); }

bool Semaphore::TimeWait(int timeout_ms) { return impl->TimeWait(timeout_ms); }

}  // namespace threadpool
}  // namespace gomros
