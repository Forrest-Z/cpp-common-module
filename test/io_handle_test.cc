
#include <gtest/gtest.h>

#include <iostream>
#include <string>

class BinaryFilter {
 private:
  uint8_t buf[4] = {0, 0, 0, 0};
  int head = 0;
  int sum = 0;
  bool pre_ret = 0, ret = 0;

 public:
  bool process(bool sig) {
    sum -= buf[head];
    buf[head] = sig;
    head = (head + 1) % sizeof(buf);
    sum += sig;

    if (sum > 2) {
      ret = true;
      pre_ret = ret;
    } else if (sum < 2) {
      ret = false;
      pre_ret = ret;
    } else {
      ret = pre_ret;
    }

    return ret;
  }
};

TEST(iohandle_test, f1) {
  std::vector<uint8_t> data = {0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
                               1, 1, 1, 0, 1, 1, 0, 0, 0, 0};
  BinaryFilter b;

  for (size_t i = 0; i < data.size(); i++) {
    usleep(10 * 1000);
    std::cout << "i= " << i << "  ret = " << b.process(data[i]) << std::endl;
  }
}