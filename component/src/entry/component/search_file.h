

#pragma once

#include <dirent.h>

#include <cstring>
#include <string>
#include <vector>

namespace gomros {
namespace entry {

/**
 * @brief 从 gomros安装路径 ， project路径 ， 数据目录 中搜索指定文件
 *
 */
class SearchFile {
 public:
  /**
   * @brief Get the File Paths object
   *
   * @param file_name 文件名， eg: "product.xml"
   * @param file_paths 返回文件路径列表,按优先级排列，eg:
   * {"/opt/gomros/run/ProductA/product.xml","/opt/gomros/run/ProductA/config/product.xml"}
   * @return true 成功
   * @return false 失败
   */
  static bool GetFilePaths(const std::string& file_name,
                           std::vector<std::string>& file_paths){};

  // 搜索指定文件夹中与指定文件名匹配的文件，并返回文件的完整路径
  bool searchFiles(const std::string& folderPath,
                   const std::string& targetFileName,
                   std::vector<std::string>& filePaths) {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(folderPath.c_str());
    if (dir == nullptr) {
      printf("Failed to open directory: ");
      return false;
    }

    while ((entry = readdir(dir)) != nullptr) {
      if (entry->d_type == DT_DIR) {
        // 忽略目录 "." 和 ".."
        if (std::string(entry->d_name) != "." &&
            std::string(entry->d_name) != "..") {
          std::string subFolderPath =
              folderPath + "/" + std::string(entry->d_name);

          if (!searchFiles(subFolderPath, targetFileName, filePaths))
            return false;
        }
      } else if (entry->d_type == DT_REG) {
        if (std::strcmp(entry->d_name, targetFileName.c_str()) == 0) {
          std::string filePath = folderPath + "/" + std::string(entry->d_name);
          filePaths.push_back(filePath);
        }
      }
    }

    closedir(dir);
  }
};

}  // namespace entry
}  // namespace gomros