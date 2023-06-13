
#include "common/time_utils.h"

#include <chrono>
#include <ctime>

namespace gomros {
namespace common {

TimestampType TimeUtils::GetTimestamp_us() {
  auto now = std::chrono::steady_clock::now();
  auto duration_since_epoch = now.time_since_epoch();

  int64_t microseconds_since_epoch =
      std::chrono::duration_cast<std::chrono::microseconds>(
          duration_since_epoch)
          .count();
  return microseconds_since_epoch;
}

std::string TimeUtils::GetFormatDateTime(bool keep_ms) {
  char buf[64];

  auto now = std::chrono::system_clock::now();
  auto duration_since_epoch = now.time_since_epoch();
  int64_t microseconds_since_epoch =
      std::chrono::duration_cast<std::chrono::microseconds>(
          duration_since_epoch)
          .count();

  time_t time_tm = std::chrono::system_clock::to_time_t(now);
  tm* date = std::localtime(&time_tm);

  int len = 0;
  if (keep_ms) {
    len = snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d,%03ld",
                   date->tm_year + 1900, date->tm_mon + 1, date->tm_mday,
                   date->tm_hour, date->tm_min, date->tm_sec,
                   microseconds_since_epoch % 1000);
  } else {
    len = snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
                   date->tm_year + 1900, date->tm_mon + 1, date->tm_mday,
                   date->tm_hour, date->tm_min, date->tm_sec);
  }

  return std::string(buf, len);
}
}  // namespace common
}  // namespace gomros
