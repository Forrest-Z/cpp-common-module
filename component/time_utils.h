
#pragma once

#include <string>

namespace common {

using TimestampType = uint64_t;

class time_utils {
 public:
 /**
  * @brief 获取当前系统时间戳，单位微秒
  * 
  * @return TimestampType 当前系统时间戳
  */
  static TimestampType GetTimestamp_us();

/**
 * @brief 获取当前格式化日期时间 , 例如："2011-12-31 12:34:56"
 * 
 * @return std::string 当前格式化日期时间
 */
  static std::string GetFormatDateTime();
};

}  // namespace common
