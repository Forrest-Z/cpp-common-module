#include <fcntl.h>
#include <gtest/gtest.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

class sigreg_test {
 private:
  /* data */
 public:
  sigreg_test() {
    auto func = [](int signum) {
      // this->sig_ipi_handler(signum);
    };
    signal(SIGIO, func);
  }
};

TEST(std, sigreg) {
  sigreg_test s;
  printf("----------");
}