
#pragma once

#include <string>

namespace common {

class file_utils {
 public:
  /**
   * @brief 读小文件内容，读到buf里面,读取大小限制为uint32
   *
   * @param filename 文件名
   * @param buf 缓存
   * @return true 读成功
   * @return false 读失败
   */
  static bool ReadSmallFile(std::string filename, std::string& buf);

  /**
   * @brief 写小文件内容，将buf里面内容写到文件里,如果文件存在，会清空原先内容
   *
   * @param filename 文件名
   * @param buf 缓存
   * @return true 写成功
   * @return false 写失败
   */
  static bool WriteSmallFile(std::string filename, std::string& buf);

  /**
 * @brief 在文件中追加内容，不会清空原先内容
 *
 * @param filename 文件名
 * @param buf 缓存
 * @return true 写成功
 * @return false 写失败
 */
  static bool AppendFile(std::string filename, std::string& buf);
};

}  // namespace common
