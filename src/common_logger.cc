
#include "include/common/common_logger.h"
#include "include/common_logger_impl.h"

// using
using common::LOG_LEVEL;
using common::Logger;

namespace common {
Logger* logger = nullptr;

void InitCommonLogger(common::LOG_LEVEL level, std::string log_file_name,
                      bool is_print_to_terminal, bool is_print_to_file) {
  if (logger == nullptr) {
    logger = new Logger(level, log_file_name, is_print_to_terminal,
                        is_print_to_file);
    printf("common logger 已设定完成 . \n");
  } else {
    printf("common logger 已经设置 , 不能重复设置 . \n");
  }
}

}  // namespace common
