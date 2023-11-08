#pragma once

#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace gomros {
namespace common {
namespace vector_utils {

template <typename V>
std::string ToString(std::vector<V>& vec) {
  std::stringstream ss;

  for (auto& i : vec) {
    ss << i << " , ";
  }

  return ss.str();
}

std::string ToString(std::map<std::string, std::string>& m) {
  std::stringstream ss;

  for (auto& i : m) {
    ss << i.first << " , " << i.second << std::endl;
  }

  return ss.str();
}
}  // namespace vector_utils
}  // namespace common
}  // namespace gomros