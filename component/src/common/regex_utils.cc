#include "regex_utils.h"

#include <iostream>
#include <regex>
#include <string>

#include "log/log.h"
#include "vector_utils.h"

bool gomros::common::regex_utils::Search(const std::string& pattern,
                                         const std::string& input,
                                         bool ignore_case) {
  std::regex pat;
  if (ignore_case) {
    pat = std::regex(pattern, std::regex_constants::icase);
  } else {
    pat = std::regex(pattern);
  }

  if (std::regex_search(input, pat)) {
    return true;
  }

  return false;
}

void gomros::common::regex_utils::Filter(const std::string& pattern,
                                         std::vector<std::string>& input,
                                         bool ignore_case) {
  LOG_INFO("pattern=%s , before=%s", pattern.c_str(),
           vector_utils::ToString(input).c_str());

  auto i = input.begin();
  while (i != input.end()) {
    if (Search(pattern, *i, ignore_case)) {
      i++;
    } else {
      i = input.erase(i);
    }
  }

  LOG_INFO("pattern=%s , after=%s", pattern.c_str(),
           vector_utils::ToString(input).c_str());
}
