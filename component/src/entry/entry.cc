
#include "log/log.h"
#include "process/start_process.h"
#include "entry.h"

#include <sstream>
#include <vector>

// 主入口
int Entry(int argc, char** argv) {
  // 解析参数
  std::vector<std::string> params;

  std::stringstream ss;
  for (int i = 0; i < argc; i++) {
    ss << "arg[" << i << "] = " << argv[i] << "  ";
    params.push_back(std::string(argv[i]));
  }
  LOG_INFO("%s\n", ss.str().c_str());

  // 一堆  if else 分支判断
  if (params[1] == "-product") {
    // start product
    gomros::entry::StartProcess::StartProduct();

  } else if (params[1] == "-process") {
    // start process
    gomros::entry::StartProcess::StartSingleProcess(params[2]);
  }
}