
#include "include/common/HexConverter.h"

#include <set>

#include "include/common_logger_impl.h"

namespace common {

bool HexToCharArray(const std::string &hex, std::vector<char> *out) {
  if (hex.size() % 2 != 0) {
    error_log("size is odd . \n");
    return false;
  }

  {
    std::set<char> dict_set = {'0', '1', '2', '3', '4', '5', '6', '7',
                               '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    for (auto c : hex) {
      if (dict_set.find(c) == dict_set.end()) {
        error_log("wrong char in hex , c=%s \n", c);
        return false;
      }
    }
  }

  out->clear();
  out->reserve(hex.size() / 2);

  for (size_t i = 0; i < hex.length(); i += 2) {
    std::string byte = hex.substr(i, 2);
    char chr = (char)(int)strtol(byte.c_str(), NULL, 16);  // NOLINT
    out->push_back(chr);
  }
  return true;
}

bool CharArrayToHex(const std::vector<char> &array, std::string *out_hex) {
  if ((array.size() * 2 < out_hex->max_size()) || (array.size() <= 0)) {
    debug_log("size error ! \n");
    return false;
  }

  const std::string dict = "0123456789ABCDEF";
  out_hex->clear();
  out_hex->reserve(array.size() * 2);

  for (auto c : array) {
    out_hex->push_back(dict[(unsigned char)c >> 4]);
    out_hex->push_back(dict[(unsigned char)c & 0xf]);
  }

  return true;
}
}  // namespace common
