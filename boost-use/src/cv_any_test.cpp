
#include <gtest/gtest.h>

#include <condition_variable>
#include <mutex>
#include <thread>

// recursive_mutex  不能与 condition_variable_any 结合使用

std::recursive_mutex rmtx;
std::condition_variable_any cv;

auto func1 = []() {
  std::unique_lock<std::recursive_mutex> lck(rmtx);
  printf("lck(rmtx)\n");
  cv.wait(lck);
  printf("cv wait end \n");
};

TEST(std, cv_any) {
  auto func2 = []() {
    std::unique_lock<std::recursive_mutex> lck(rmtx);
    printf("func2 start \n");
    func1();
    printf("func2 end \n");
  };

  std::thread t(func2);

  sleep(3);

  {
    std::unique_lock<std::recursive_mutex> lck(rmtx);
    cv.notify_all();
    printf("cv.notify_all \n");
  }
  t.join();
}