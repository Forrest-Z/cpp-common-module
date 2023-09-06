#pragma once

#include <string>

namespace gomros {
namespace common {
namespace regex_utils {

bool Search(const std::string &pattern, const std::string &input,
            bool ignore_case = true);
}
}
}