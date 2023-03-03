
#include "include/common/log.h"

#include "include/log_impl.h"

namespace common {

constexpr size_t MAX_LOG_MSG_SIZE = UINT16_MAX;

Logger::Logger(LOG_LEVEL level, std::string log_file_name,
               bool is_print_to_terminal) {
  logger_impl_ = std::make_shared<LoggerImpl>(level, log_file_name,
                                              is_print_to_terminal, true);
}

Logger::Logger(LOG_LEVEL level, std::string log_file_name,
               bool is_print_to_terminal, bool is_print_to_file) {
  logger_impl_ = std::make_shared<LoggerImpl>(
      level, log_file_name, is_print_to_terminal, is_print_to_file);
}

Logger::~Logger() {}

void Logger::WriteLog(LOG_LEVEL writelevel, const char* fileName, int line,
                      const char* func, const char* format, ...) {
  va_list args;
  va_start(args, format);

  char message[MAX_LOG_MSG_SIZE + 1] = {0};
  vsnprintf(message, MAX_LOG_MSG_SIZE, format, args);

  logger_impl_->WriteLog(writelevel, fileName, line, func, message);

  va_end(args);
}

}  // namespace common
