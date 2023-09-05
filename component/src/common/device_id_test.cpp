
#include "common/device_id.h"
#include <gtest/gtest.h>

TEST(common, device_id) {
  printf("-----------test start------------\n");

  gomros::common::DeviceID id;

  std::string device_id;
  id.Get(device_id);

  std::cout << "device_id : " << device_id << std::endl;
}