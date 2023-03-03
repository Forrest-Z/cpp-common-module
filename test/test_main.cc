/*
 * @Description: Copyright (C) 2022 山东亚历山大智能科技有限公司
 * @Version: 1.0
 * @Author: tong
 * @Date: 2022-07-06 18:11:39
 * @LastEditTime: 2022-07-07 16:34:17
 */

#include <gtest/gtest.h>
#include "include/common/backtrace.h"

GTEST_API_ int main(int argc, char **argv) {
  // int ret = system("mkdir -p out");

  testing::InitGoogleTest(&argc, argv);

  common::ErrorBacktraceRegister();

  auto ret = RUN_ALL_TESTS();
  return ret;
}
