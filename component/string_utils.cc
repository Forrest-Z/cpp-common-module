
#include "string_utils.h"
namespace common {

void string_utils::SplitString(const std::string& input, char delimiter,
                               std::vector<std::string>& ret,
                               bool keep_middle_empty_str,
                               bool keep_end_empty_str) {
  std::stringstream ss(input);
  std::string item;

  ret.clear();
  while (std::getline(ss, item, delimiter)) {
    // 不保留空字符串
    if ((!keep_middle_empty_str) && item.empty()) {
      continue;
    }

    ret.push_back(item);
  }

  // 保留结尾空字符串
  if (keep_end_empty_str && (input.back() == delimiter)) {
    ret.push_back("");
  }
}

bool string_utils::DecodeParams(const std::string& input, ParamsType& ret,
                                char key_val_delimiter, char field_delimiter) {
  std::vector<std::string> strs;
  SplitString(input, field_delimiter, strs);

  ret.clear();

  // 遍历strs,每个字符串通过key_val_delimiter分割成key、val放入字典，格式错误返回失败
  for (auto& str : strs) {
    std::vector<std::string> param_strs;
    SplitString(str, key_val_delimiter, param_strs, true, true);
    if (param_strs.size() != 2) {
      printf("input format wrong . \n");
      return false;
    }

    ret[param_strs[0]] = param_strs[1];
  }

  return true;
}
bool string_utils::EncodeParams(const ParamsType& params, std::string& ret,
                                char key_val_delimiter, char field_delimiter) {
  ret.clear();

  for (auto& param : params) {
    ret.append(param.first).push_back(key_val_delimiter);
    ret.append(param.second).push_back(field_delimiter);
  }

  return true;
}

}  // namespace common