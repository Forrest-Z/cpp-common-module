/**
 * @file search_file.cc
 * @author 童汉森 (ths)
 * @brief
 * @version 1.0
 * @date 2023-07-15
 *
 * 山东亚历山大智能科技有限公司 Copyright (c) 2023
 *
 */

#include "search_file.h"
#include "log/log.h"

#include <dirent.h>

#include <cstring>
#include <string>
#include <vector>

namespace gomros {
namespace entry {

bool SearchFile::GetFilePaths(const std::vector<std::string> &search_paths,
                              const std::string &file_name,
                              std::vector<std::string> &file_paths) {
  file_paths.clear();
  bool ret = true;
  for (auto &i : search_paths) {
    ret &= SearchFiles(i, file_name, file_paths);
  }

  for (auto &i : file_paths) {
    LOG_DEBUG("%s", i.c_str());
  }

  return ret;
}

// 搜索指定文件夹中与指定文件名匹配的文件，并返回文件的所在目录
bool SearchFile::SearchFiles(const std::string &folderPath,
                             const std::string &targetFileName,
                             std::vector<std::string> &filePaths) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(folderPath.c_str());
  if (dir == nullptr) {
    LOG_DEBUG("Failed to open directory: %s ", folderPath.c_str());
    return false;
  }

  while ((entry = readdir(dir)) != nullptr) {
    if (entry->d_type == DT_DIR) {
      // LOG_DEBUG("%s ", entry->d_name);
      // 忽略目录 "." 和 ".."
      if (std::string(entry->d_name) != "." &&
          std::string(entry->d_name) != "..") {
        std::string subFolderPath =
            folderPath + "/" + std::string(entry->d_name);

        if (!SearchFiles(subFolderPath, targetFileName, filePaths))
          return false;
      }
    } else if (entry->d_type == DT_REG) {
      // LOG_DEBUG("%s ", entry->d_name);
      if (std::strcmp(entry->d_name, targetFileName.c_str()) == 0) {
        // std::string filePath = folderPath + "/" +
        // std::string(entry->d_name);
        std::string filePath = folderPath;
        filePaths.push_back(filePath);
      }
    }
  }

  closedir(dir);
  return true;
}

} // namespace entry
} // namespace gomros
