/**
 * @file FileUtils.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <string>

namespace gomros {
namespace common {

/**
 * @brief 文件处理类
 *
 */
class FileUtils {
 public:
  /**
   * @brief 读小文件内容，读到buf里面,读取大小限制为uint32
   *
   * @param filename 文件名
   * @param buf 缓存
   * @return true 读成功
   * @return false 读失败
   */
  static bool ReadSmallFile(const std::string& filename, std::string& buf);

  /**
   * @brief 写小文件内容，将buf里面内容写到文件里,如果文件存在，会清空原先内容
   *
   * @param filename 文件名
   * @param buf 缓存
   * @return true 写成功
   * @return false 写失败
   */
  static bool WriteSmallFile(const std::string& filename, std::string& buf);

  /**
 * @brief 在文件中追加内容，不会清空原先内容
 *
 * @param filename 文件名
 * @param buf 缓存
 * @return true 写成功
 * @return false 写失败
 */
  static bool AppendFile(const std::string& filename, std::string& buf);

/**
 * @brief 递归创建多级目录，如果目录不存在会创建，目录存在不影响原先的目录下内容
 * 
 * @param path 递归创建目录
 * @return true 成功
 * @return false 失败
 */
  static bool CreateDirectories(const std::string& path);
};

}  // namespace common
}  // namespace gomros

