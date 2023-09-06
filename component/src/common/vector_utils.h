#pragma once

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
}
}
}