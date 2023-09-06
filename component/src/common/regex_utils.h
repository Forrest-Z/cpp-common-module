#pragma once

#include <string>
#include <vector>

namespace gomros {
namespace common {
namespace regex_utils {

bool Search(const std::string &pattern, const std::string &input,
            bool ignore_case = true);

void Filter(const std::string &pattern, std::vector<std::string> &input,
            bool ignore_case = true);
}
}
}