
#include "clv602_protocol.h"

#include <gtest/gtest.h>

#include "common/time_utils.h"

TEST(test, clv602_noread) {
  printf("-----------test start------------\n");

  gomros::device::Clv602Protocol pro;

  std::string data = "#NoRead%";
  std::string result;
  EXPECT_EQ(pro.Process(data.data(), data.size(), result),
            gomros::device::Clv602Protocol::RetType::NoRead);
  printf("result = %s \n", result.c_str());
}

TEST(test, clv602_readsuccess) {
  printf("-----------test start------------\n");

  gomros::device::Clv602Protocol pro;

  std::string data = "#*ABC-1234*%";
  std::string result;
  EXPECT_EQ(pro.Process(data.data(), data.size(), result),
            gomros::device::Clv602Protocol::RetType::ReadSuccess);
  printf("result = %s \n", result.c_str());
}

TEST(test, clv602_readhalf) {
  printf("-----------test start------------\n");

  gomros::device::Clv602Protocol pro;

  std::string data = "#*ABC-";
  std::string result;
  EXPECT_EQ(pro.Process(data.data(), data.size(), result),
            gomros::device::Clv602Protocol::RetType::ProcessFail);
  printf("result = %s \n", result.c_str());

  data = "1234*%";
  EXPECT_EQ(pro.Process(data.data(), data.size(), result),
            gomros::device::Clv602Protocol::RetType::ReadSuccess);
  printf("result = %s \n", result.c_str());
}