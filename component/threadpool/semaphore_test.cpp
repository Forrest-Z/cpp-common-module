
#include "semaphore.h"
#include <gtest/gtest.h>
#include <thread>

#include "./../time_utils.h"

TEST(common, component_sema) {
  auto sema = std::make_shared<common::semaphore>(0);
  const int num = 20;

  auto func = [](int id, std::shared_ptr<common::semaphore> sema) {
    std::this_thread::sleep_for(std::chrono::seconds(id));
    sema->signal();
    std::cout << id << " is end ." << std::endl;
  };

  {
    std::vector<std::thread> thread_pool;

    for (size_t i = 0; i < num; i++) {
      thread_pool.push_back(std::move(std::thread(func, i, sema)));
    }

    // 等待所有线程退出
    for (size_t i = 0; i < num; i++) {
      sema->wait();
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
    auto deadline = 10 * 1000 + common::time_utils::GetTimestamp_us() / 1000;

    std::cout << "deadline : " << deadline << std::endl;

    for (size_t i = 0; i < num; i++) {
      auto delta = deadline - common::time_utils::GetTimestamp_us() / 1000;
          std::cout << "delta : " << delta << std::endl;
      if (!sema->time_wait(std::chrono::microseconds(delta))) break;
    }
    for (auto &t : thread_pool) t.detach();
    std::cout << "some thread exit ." << std::endl;
  }
}
