
#include "entry.h"
#include "args_handle.h"
#include "log/log.h"
#include "process/start_process.h"

#include <sstream>
#include <vector>

// 主入口
int Entry(int argc, char** argv) {
  // 解析参数
  std::vector<std::string> raw_strs;

  std::stringstream ss;
  for (int i = 0; i < argc; i++) {
    ss << "arg[" << i << "] = " << argv[i] << "  ";
    raw_strs.push_back(std::string(argv[i]));
  }
  LOG_INFO("%s", ss.str().c_str());

  // decode args
  std::map<std::string, std::vector<std::string>> cmd_map;
  gomros::entry::ArgsHandle::Decode(raw_strs, cmd_map);

  // 一堆  if else 分支判断

  if (cmd_map.find("-add_component_path") != cmd_map.end()) {
    // add component path
  }

  if (cmd_map.find("-product") != cmd_map.end()) {
    // start product
    gomros::entry::StartProcess::StartProduct();

  } else if (cmd_map.find("-process") != cmd_map.end()) {
    // start process
    auto params = cmd_map["-process"];
    if (params.size() >= 1) {
      gomros::entry::StartProcess::StartSingleProcess(params[0]);
    } else {
      LOG_ERROR("params wrong .");
    }
  }
}