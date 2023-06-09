
#include "time_utils.h"
#include <gtest/gtest.h>

TEST(common, component_timeutils) {
  printf("-----------test start------------\n");

  std::cout << "format time :" << common::time_utils::GetFormatDateTime()
            << std::endl;
  std::cout << "format time ms :" << common::time_utils::GetFormatDateTime(true)
            << std::endl;

  std::cout << "timestamp :" << common::time_utils::GetTimestamp_us()
            << std::endl;
}
