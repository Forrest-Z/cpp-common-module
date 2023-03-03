#pragma once

#include <string>
#include "./log.h"

namespace common {

/**
 * @brief init commonlogger
 * @param level 日志设定等级
 * @param log_file_name 日志文件名称
 * @param is_print_to_terminal 是否打印到终端
 * @param is_print_to_file 是否打印到文件
 */
void InitCommonLogger(common::LOG_LEVEL level,
                      std::string log_file_name, bool is_print_to_terminal,
                      bool is_print_to_file);

}  // namespace common
