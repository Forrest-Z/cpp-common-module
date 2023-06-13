
#include "common/semaphore.h"
#include <gtest/gtest.h>
#include <thread>

#include "common/time_utils.h"

TEST(common, component_sema) {
  auto sema = std::make_shared<gomros::common::Semaphore>(0);
  const int num = 10;

  auto func = [](int id, std::shared_ptr<gomros::common::Semaphore> sema) {
    std::this_thread::sleep_for(std::chrono::seconds(id));
    sema->Signal();
    std::cout << id << " is end ." << std::endl;
  };

  {
    std::vector<std::thread> thread_pool;

    for (size_t i = 0; i < num; i++) {
      thread_pool.push_back(std::move(std::thread(func, i, sema)));
    }

    // 等待所有线程退出
    for (size_t i = 0; i < num; i++) {
      sema->Wait();
    }
    for (auto &t : thread_pool) t.detach();
    std::cout << "all thread exit ." << std::endl;
  }

  {
    std::vector<std::thread> thread_pool;

    for (size_t i = 0; i < num; i++) {
      thread_pool.push_back(std::move(std::thread(func, i, sema)));
    }

    // 等待所有线程退出
    auto deadline =
        5 * 1000 + gomros::common::TimeUtils::GetTimestamp_us() / 1000;

    std::cout << "deadline : " << deadline << std::endl;

    for (size_t i = 0; i < num; i++) {
      auto delta =
          deadline - gomros::common::TimeUtils::GetTimestamp_us() / 1000;
      std::cout << "delta : " << delta << std::endl;
      if (!sema->TimeWait(std::chrono::milliseconds(delta))) break;
    }
    for (auto &t : thread_pool) t.detach();
    std::cout << "some thread exit ." << std::endl;
  }
}
