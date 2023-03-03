#pragma once

#include <string>
#include "./common/log.h"

namespace gomros {
namespace common {

extern common::Logger* logger;

#define error_log(format, ...)           \
  if (common::logger != nullptr) \
  ERROR_LOG(common::logger, format, ##__VA_ARGS__)

#define warning_log(format, ...)         \
  if (common::logger != nullptr) \
  WARN_LOG(common::logger, format, ##__VA_ARGS__)

#define info_log(format, ...)            \
  if (common::logger != nullptr) \
  INFO_LOG(common::logger, format, ##__VA_ARGS__)

#define debug_log(format, ...)           \
  if (common::logger != nullptr) \
  DEBUG_LOG(common::logger, format, ##__VA_ARGS__)

}  // namespace common
}  // namespace gomros
