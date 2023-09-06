#include "regex_utils.h"

#include <iostream>
#include <regex>
#include <string>

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