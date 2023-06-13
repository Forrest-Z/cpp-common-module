
#include "common/time_utils.h"
#include <gtest/gtest.h>

TEST(common, component_timeutils) {
  printf("-----------test start------------\n");

  std::cout << "format time :" << gomros::common::TimeUtils::GetFormatDateTime()
            << std::endl;
  std::cout << "format time ms :" << gomros::common::TimeUtils::GetFormatDateTime(true)
            << std::endl;

  std::cout << "timestamp :" << gomros::common::TimeUtils::GetTimestamp_us()
            << std::endl;
}
