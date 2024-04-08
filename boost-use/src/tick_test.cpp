#include <gtest/gtest.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

void p_time() {
  static auto pre = std::chrono::steady_clock::now();
  auto now = std::chrono::steady_clock::now();

  std::cout << "time diff us: "
            << std::chrono::duration_cast<std::chrono::microseconds>(now - pre)
                   .count()
            << std::endl;
  pre = now;
}

class tick_test {
 public:
  std::mutex mtx;
  std::condition_variable cv;

  std::thread t;

 public:
  tick_test() {
    auto func = [this]() {
      {
        int cc = 10000;
        while (cc--) {
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
          std::unique_lock<std::mutex> lck(this->mtx);
          this->cv.notify_all();
        }
      }
    };
    t = std::thread(func);
    t.detach();
  }

  bool WaitTick(int timeout_ms) {
    std::unique_lock<std::mutex> lck(mtx);
    auto ret = cv.wait_for(lck, std::chrono::milliseconds(timeout_ms));
    return (ret == std::cv_status::no_timeout);
  }
};

TEST(std, tick_test) {
  auto ins = new tick_test();
  while (true) {
    ins->WaitTick(1000);
    p_time(); /* code */
  }
}