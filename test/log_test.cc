
#include "include/common/log.h"

#include <gtest/gtest.h>

#include <iostream>

static void debug_logger_test() {
  auto logger = std::make_shared<common::Logger>(common::LOG_LEVEL::DEBUG,
                                                 "debug", true, true);
  std::string s = "string_data";
  DEBUG_LOG(logger, "number : %d ,string =  %s .\n", 3, s.c_str());
  INFO_LOG(logger, "info msg .\n");
  WARN_LOG(logger, "warning msg .\n");
  ERROR_LOG(logger, "error msg .\n");
}

static void info_logger_test() {
  auto logger =
      std::make_shared<common::Logger>(common::LOG_LEVEL::INFO, "info", true);
  std::string s = "string_data";
  DEBUG_LOG(logger, "number : %d ,string =  %s .\n", 3, s.c_str());
  INFO_LOG(logger, "info msg .\n");
  WARN_LOG(logger, "warning msg .\n");
  ERROR_LOG(logger, "error msg .\n");
}

static void warning_logger_test() {
  auto logger = std::make_shared<common::Logger>(common::LOG_LEVEL::WARNING,
                                                 "warning", true);
  std::string s = "string_data";
  DEBUG_LOG(logger, "number : %d ,string =  %s .\n", 3, s.c_str());
  INFO_LOG(logger, "info msg .\n");
  WARN_LOG(logger, "warning msg .\n");
  ERROR_LOG(logger, "error msg .\n");
}

static void error_logger_test() {
  auto logger =
      std::make_shared<common::Logger>(common::LOG_LEVEL::ERROR, "error", true);
  std::string s = "string_data";
  DEBUG_LOG(logger, "number : %d ,string =  %s .\n", 3, s.c_str());
  INFO_LOG(logger, "info msg .\n");
  WARN_LOG(logger, "warning msg .\n");
  ERROR_LOG(logger, "error msg .\n");
}

TEST(log_test, printf) {
  printf("------------------------------\n");
  debug_logger_test();
  printf("------------------------------\n");
  info_logger_test();
  printf("------------------------------\n");
  warning_logger_test();
  printf("------------------------------\n");
  error_logger_test();
}
