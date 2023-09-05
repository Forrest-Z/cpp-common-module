
#include "common/device_id.h"
#include <gtest/gtest.h>

TEST(common, device_id) {
  printf("-----------test start------------\n");

  gomros::common::DeviceID id;

  std::string device_id;
  id.Get(device_id);

  std::cout << "device_id(MAC) : " << device_id << std::endl;

  id.Get(device_id, "HardDriveSerial");

  std::cout << "device_id(HardDriveSerial) : " << device_id << std::endl;
}