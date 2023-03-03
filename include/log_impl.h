
#pragma once

#include <string>
#include "./common/log.h"

#include <log4cpp/Category.hh>  // NOLINT

namespace common {

class LoggerImpl {
 private:
  /* data */
  enum LOG_LEVEL level;
  std::string log_file_name;
  bool is_print_to_terminal;
  bool is_print_to_file;

  log4cpp::Category& root;

 public:
  LoggerImpl(LOG_LEVEL level, std::string log_file_name,
             bool is_print_to_terminal, bool is_print_to_file);
  ~LoggerImpl();
  std::string getDateTime(bool onlynum, time_t timestamp);
  std::string getMsDateTime();

  void WriteLog(LOG_LEVEL writelevel, const char* fileName, int line,
                const char* func, const char* msg);
};
}  // namespace common
