
#include "time_utils.h"

#include <ctime>

#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

namespace common {

TimestampType time_utils::GetTimestamp_us() {
  struct timeval stamp;
  gettimeofday(&stamp, NULL);
  TimestampType ret = stamp.tv_sec * 1000000 + stamp.tv_usec;
  return ret;
}

std::string time_utils::GetFormatDateTime() {
  char buf[64];

  auto t = std::time(nullptr);
  auto date = std::localtime(&t);
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
           date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour,
           date->tm_min, date->tm_sec);
  return buf;
}
}  // namespace common
