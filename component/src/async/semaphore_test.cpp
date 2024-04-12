
#include "async/semaphore.h"

#include <gtest/gtest.h>

#include <thread>

#include "common/time_utils.h"

TEST(async, component_sema) {
  auto sema = std::make_shared<gomros::async::Semaphore>(0);
  const int num = 10;

  auto func = [](int id, std::shared_ptr<gomros::async::Semaphore> sema) {
    std::this_thread::sleep_for(std::chrono::seconds(id));
    sema->Signal();
    std::cout << id << " is end ." << std::endl;
  };

  {
    std::vector<std::thread> async;

    for (size_t i = 0; i < num; i++) {
      async.push_back(std::move(std::thread(func, i, sema)));
    }

    // 等待所有线程退出
    for (size_t i = 0; i < num; i++) {
      sema->Wait();
    }
    for (auto &t : async) t.detach();
    std::cout << "all thread exit ." << std::endl;
  }

  {
    std::vector<std::thread> async;

    for (size_t i = 0; i < num; i++) {
      async.push_back(std::move(std::thread(func, i, sema)));
    }

    // 等待所有线程退出
    auto deadline =
        5 * 1000 + gomros::common::TimeUtils::GetTimestamp_us() / 1000;

    std::cout << "deadline : " << deadline << std::endl;

    for (size_t i = 0; i < num; i++) {
      auto delta =
          deadline - gomros::common::TimeUtils::GetTimestamp_us() / 1000;
      std::cout << "delta : " << delta << std::endl;
      if (!sema->TimeWait(delta)) break;
    }
    for (auto &t : async) t.detach();
    std::cout << "some thread exit ." << std::endl;
  }
}

TEST(async, sema_interval) {
  auto sema = gomros::async::Semaphore("test", 1);
  printf("signal . \n");

  auto func = []() {
    auto sema = gomros::async::Semaphore("test", 0);

    for (size_t i = 0; i < 2; i++) {
      sema.Wait();
      printf("wait success . \n");
    }
  };

  auto t = std::thread(func);

  sleep(5);
  sema.Signal();
  sleep(5);
  sema.Signal();

  t.join();
}

TEST(async, sema_proc) {
  int p = fork();
  if (p != 0) {
    printf("child \n");
    auto sema = gomros::async::Semaphore("test", 0);

    for (size_t i = 0; i < 2; i++) {
      sema.Wait();
      printf("wait success . \n");
      printf("w: %s \n",
             gomros::common::TimeUtils::GetFormatDateTime(true).c_str());
    }
    return;
  } else {
    printf("father \n");
    auto sema = gomros::async::Semaphore("test", 0);

    sleep(5);
    printf("signal . \n");
    printf("%s \n", gomros::common::TimeUtils::GetFormatDateTime(true).c_str());
    sema.Signal();
    
    sleep(5);
    printf("%s \n", gomros::common::TimeUtils::GetFormatDateTime(true).c_str());
    sema.Signal();
  }
}
