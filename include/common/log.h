
#pragma once

#include <cstring>
#include <memory>
#include <string>

namespace common {

class LoggerImpl;

/**
 * @brief log 等级
 *
 */
typedef enum LOG_LEVEL {
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3
} LOG_LEVEL;

/**
 * @brief 日志类
 *
 * 日志类使用：在库里面自己实例化日志类，默认等级设定为warning；
 * 外部可以通过传配置参数在构造函数设置日志类；
 */
class Logger {
 private:
  std::shared_ptr<LoggerImpl> logger_impl_;

 public:
  /**
   * @brief Construct a new Logger object
   *
   * @param level 设定日志等级，实际打印会打印高于这个等级的日志
   * @param log_file_name 日志文件名，该文件会存在
   * ./log/{log_file_name + date}.log
   * @param is_print_to_terminal
   * 设定是否打印到终端，默认打印到文件，true:打印到终端，false:不打印到终端
   */
  Logger(LOG_LEVEL level, std::string log_file_name, bool is_print_to_terminal);

  /**
   * @brief Construct a new Logger object
   *
   * @param level 设定日志等级，实际打印会打印高于这个等级的日志
   * @param log_file_name 日志文件名，该文件会存在
   * ./log/{log_file_name + date}.log
   * @param is_print_to_terminal 设定是否打印到终端，true:打印到终端
   * ，false:不打印到终端
   * @param is_print_to_file 设定是否打印到文件
   */
  Logger(LOG_LEVEL level, std::string log_file_name, bool is_print_to_terminal,
         bool is_print_to_file);
  ~Logger();

  /**
   * @brief 写日志接口，请勿直接使用
   *
   * @param writelevel 设定写入等级
   * @param fileName 写日志所在文件
   * @param line 写日志所在行
   * @param func 写日志所在的函数
   * @param format 格式
   * @param ... 参数
   */
  void WriteLog(LOG_LEVEL writelevel, const char* fileName, int line,
                const char* func, const char* format, ...);
};

#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define ERROR_LOG(logger_pointer, format, ...)                             \
  logger_pointer->WriteLog(common::LOG_LEVEL::ERROR, __FILENAME__, \
                           __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define INFO_LOG(logger_pointer, format, ...)                             \
  logger_pointer->WriteLog(common::LOG_LEVEL::INFO, __FILENAME__, \
                           __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define WARN_LOG(logger_pointer, format, ...)                                \
  logger_pointer->WriteLog(common::LOG_LEVEL::WARNING, __FILENAME__, \
                           __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define DEBUG_LOG(logger_pointer, format, ...)                             \
  logger_pointer->WriteLog(common::LOG_LEVEL::DEBUG, __FILENAME__, \
                           __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

}  // namespace common
