#pragma once

#include "log/log.h"

#include <map>
#include <string>
#include <vector>


namespace gomros {
namespace entry {

class ArgsHandle {
 public:
  // -cmd1 parms1 parms2  -cmd2 parms3
  static bool Decode(const std::vector<std::string>& raw_strs,
                     std::map<std::string, std::vector<std::string>>& cmd_map) {
    if (raw_strs.size() <= 1) {
      return false;
    }

    cmd_map.clear();

    std::string temp_cmd = " ";

    for (size_t i = 1; i < raw_strs.size(); i++) {
      if (raw_strs[i].front() == '-') {
        std::vector<std::string> null_params;
        cmd_map.insert({raw_strs[i], null_params});
        temp_cmd = raw_strs[i];
      } else {
        cmd_map[temp_cmd].push_back(raw_strs[i]);
      }
    }

    for (auto& i : cmd_map) {
      LOG_DEBUG("cmd = %s , params size = %lu ", i.first.c_str(),
                i.second.size());
    }

    return true;
  }
};

}  // namespace entry
}  // namespace gomros
