
#pragma once

#include <map>
#include <string>
#include <vector>

namespace common {
class string_utils {
 public:
  /**
   * @brief 根据分割符分割字符串，返回一个string的vector
   *
   * @param input 需要分割的字符串
   * @param delimiter 分割符
   * @param ret 返回的string的vector
   * @param keep_middle_empty_str
   * 是否保留中间出现的空字符串，input中间出现连续两个分割符的情况
   * @param keep_end_empty_str
   * 是否保留结尾出现的空字符串，input结尾为分割符的情况
   */
  static void SplitString(const std::string& input,
                          std::vector<std::string>& ret, char delimiter = ':',
                          bool keep_middle_empty_str = false,
                          bool keep_end_empty_str = false);

  /**
   * @brief key:val 参数字典map
   *
   */
  typedef std::map<std::string, std::string> ParamsType;

  /**
   * @brief 解码，格式如： key1:val1;key2:val2;
   *
   * @param input 要解码的字符串
   * @param ret 解码后的参数字典
   * @param key_val_delimiter key value 之间分割符
   * @param field_delimiter 两个字段间的分割符
   * @return true success
   * @return false fail
   */
  static bool DecodeParams(const std::string& input, ParamsType& ret,
                           char key_val_delimiter = ':',
                           char field_delimiter = ';');

  /**
 * @brief 编码，格式如： key1:val1;key2:val2;
 *
 * @param input 要编码的参数字典
 * @param ret 编码后的字符串
 * @param key_val_delimiter key value 之间分割符
 * @param field_delimiter 两个字段间的分割符
 * @return true success
 * @return false fail
 */
  static bool EncodeParams(const ParamsType& params, std::string& ret,
                           char key_val_delimiter = ':',
                           char field_delimiter = ';');
};

}  // namespace common
