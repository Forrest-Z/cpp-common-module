/**
 * @file search_file.h
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */

#pragma once

#include <string>
#include <vector>

namespace gomros {
namespace entry {

/**
 * @brief 从指定目录搜索文件
 *
 */
class SearchFile {
public:
  /**
   * @brief Get the File Paths object
   *
   * @param search_paths 要搜索的路径
   * @param file_name 文件名， eg: "product.xml"
   * @param file_paths 返回文件目录路径列表,按优先级排列，eg:
   * {"/opt/gomros/run/ProductA","/opt/gomros/data/ProductA/"}
   * @return true 成功
   * @return false 失败
   */
  static bool GetFilePaths(const std::vector<std::string> &search_paths,
                           const std::string &file_name,
                           std::vector<std::string> &file_paths);

private:
  // 搜索指定文件夹中与指定文件名匹配的文件，并返回文件的所在目录
  static bool SearchFiles(const std::string &folderPath,
                          const std::string &targetFileName,
                          std::vector<std::string> &filePaths);
};

} // namespace entry
} // namespace gomros
