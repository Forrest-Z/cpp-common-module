
#pragma once

#include <string>

namespace common {

typedef uint64_t TimestampType;

class time_utils {
 public:
  /**
   * @brief 获取当前系统启动时间戳，即开机运行到现在的经过的微妙
   *
   * @return TimestampType 当前系统启动时间戳
   */
  static TimestampType GetTimestamp_us();

  /**
   * @brief 获取当前格式化日期时间,时间为系统的日期时间，时区为系统设置的时区 ,
   * 例如："2011-12-31 12:34:56,146"
   * 例如："2011-12-31 12:34:56"
   *
   * @param keep_ms 是否保留到毫秒,true:保留到毫秒，false:保留到秒
   * @return std::string 格式化日期时间
   */
  static std::string GetFormatDateTime(bool keep_ms = false);
};

}  // namespace common
