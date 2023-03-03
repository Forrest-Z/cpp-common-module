/*
 * @copyright: Copyright (C) 2022 山东亚历山大智能科技有限公司
 * @file:  log_impl.cc
 * @author:  tong
 * @version:  v0.1
 */
#include "include/log_impl.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/RollingFileAppender.hh>

#include <vector>

namespace gomros {
namespace common {
std::shared_ptr<std::string> INIT_LOG_PATH = nullptr;

LoggerImpl::LoggerImpl(LOG_LEVEL level, std::string log_file_name,
                       bool is_print_to_terminal, bool is_print_to_file)
    : root(log4cpp::Category::getRoot().getInstance(log_file_name)) {
  this->level = level;
  this->is_print_to_terminal = is_print_to_terminal;
  this->is_print_to_file = is_print_to_file;

  if (nullptr == INIT_LOG_PATH) {
    INIT_LOG_PATH = std::make_shared<std::string>(
        std::string("log/") + getMsDateTime() + std::string("/"));
  }

  log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
  pLayout->setConversionPattern("%d: %p %c %x: %m");

  auto re = system((std::string("mkdir -p ") + *INIT_LOG_PATH).c_str());

  auto appender_name = log_file_name;

  if (root.getAppender(appender_name) == nullptr) {
    log4cpp::Appender* fileAppender = new log4cpp::FileAppender(
        appender_name, *INIT_LOG_PATH + log_file_name + ".log");
    fileAppender->setLayout(pLayout);
    root.addAppender(fileAppender);

    {
      log4cpp::Appender* f_appender = new log4cpp::FileAppender(
          appender_name, *INIT_LOG_PATH + "gomros.log");
      f_appender->setLayout(pLayout);
      root.addAppender(f_appender);
    }
  }

  root.setPriority(log4cpp::Priority::DEBUG);
}

LoggerImpl::~LoggerImpl() {}

std::string LoggerImpl::getDateTime(bool onlynum = true,
                                    time_t timestamp = time(NULL)) {
  char buffer[20] = {0};
  struct tm* info = localtime(&timestamp);  // NOLINT
  if (onlynum) {
    strftime(buffer, sizeof buffer, "%Y%m%d%H%M%S", info);
  } else {
    strftime(buffer, sizeof buffer, "%Y/%m/%d %H:%M:%S", info);
  }
  return std::string(buffer);
}

std::string LoggerImpl::getMsDateTime() {
  std::string sTimestamp;
  char acTimestamp[40];
  struct timeval tv;
  struct tm* tm;
  gettimeofday(&tv, NULL);
  tm = localtime(&tv.tv_sec);                                       // NOLINT
  sprintf(acTimestamp, "%02d%02d%02d%02d%02d", tm->tm_year + 1900,  // NOLINT
          tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
  sTimestamp = acTimestamp;
  return sTimestamp;
}

void LoggerImpl::WriteLog(LOG_LEVEL writelevel, const char* fileName, int line,
                          const char* func, const char* msg) {
  if (is_print_to_terminal) {
    if (writelevel >= level) {
      if (writelevel == WARNING) {
        printf("\033[1;33mFile:%s, Line:%d, Func:%s, %s\033[0m", fileName, line,
               func, msg);
      } else if (writelevel == ERROR) {
        printf("\033[0;31mFile:%s, Line:%d, Func:%s, %s\033[0m", fileName, line,
               func, msg);
      } else {
        printf("\033[1;34mFile:%s, Line:%d, Func:%s, %s\033[0m", fileName, line,
               func, msg);
      }
    }
  }

  if ((is_print_to_file) && (writelevel >= level)) {
    if (writelevel == WARNING) {
      root.warn("%s, %d, %s : %s", fileName, line, func, msg);
    } else if (writelevel == ERROR) {
      root.error("%s, %d, %s : %s", fileName, line, func, msg);
    } else if (writelevel == DEBUG) {
      root.debug("%s, %d, %s : %s", fileName, line, func, msg);
    } else {
      root.info("%s, %d, %s : %s", fileName, line, func, msg);
    }
  }
}
}  // namespace common
}  // namespace gomros
