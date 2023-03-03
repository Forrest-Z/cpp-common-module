/*
 * @copyright: Copyright (C) 2022 山东亚历山大智能科技有限公司
 * @file:  common_logger.cc
 * @author:  tong
 * @version:  v0.1
 */

#include <mutex>   // NOLINT
#include <thread>  // NOLINT
#include <unordered_map>

#include "include/common_lib/common_logger.h"
#include "include/common_lib/time_utils.h"
#include "include/common_logger_impl.h"

// using
using gomros::common::Logger;
using gomros::common::LOG_LEVEL;

namespace gomros {
namespace common {

// static
static Logger* setting_logger_ = nullptr;
Logger* logger = nullptr;
static std::thread* monitor_thread_ = nullptr;
static std::unordered_map<std::string, std::string> monitor_logger_data_map;
static std::mutex monitor_logger_data_map_mtx;

static void MonitorLoggerThread(void) {
  while (true) {
    gomros::common::Sleep_ms(1000 * 5);
    {
      std::lock_guard<std::mutex> lck(monitor_logger_data_map_mtx);
      std::string ret = "\n";
      char s[UINT16_MAX] = "";
      int num = 0;

      for (auto& elem : monitor_logger_data_map) {
        num = snprintf(s, sizeof(s), "id = %s , msg = %s\n", elem.first.c_str(),
                       elem.second.c_str());
        ret += std::string(s, num);
      }

      info_log("%s", ret.c_str());
    }
  }
}

void MonitorLoggerRefreshInfo(std::string id, std::string msg) {
  std::lock_guard<std::mutex> lck(monitor_logger_data_map_mtx);

  auto ret = monitor_logger_data_map.find(id);
  if (ret == monitor_logger_data_map.end()) {  // not find
    monitor_logger_data_map.insert(
        std::pair<std::string, std::string>(id, msg));
  } else {
    monitor_logger_data_map[id] = msg;
  }
}

void InitCommonLogger(gomros::common::LOG_LEVEL level,
                      std::string log_file_name, bool is_print_to_terminal,
                      bool is_print_to_file) {
  if (setting_logger_ == nullptr) {
    setting_logger_ = new Logger(level, log_file_name, is_print_to_terminal,
                                 is_print_to_file);
    logger = setting_logger_;
    printf("common logger 已设定完成 . \n");
  } else {
    printf("setting_logger_ 已经设置 , 不能重复设置 . \n");
  }

  if (monitor_thread_ == nullptr) {
    monitor_thread_ = new std::thread(MonitorLoggerThread);
  }
}

}  // namespace common
}  // namespace gomros
