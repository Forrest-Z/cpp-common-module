

#include "search_file.h"
#include "log/log.h"

#include <dirent.h>

#include <cstring>
#include <string>
#include <vector>

namespace gomros {
namespace entry {
SearchFile* SearchFile::instance = nullptr;

SearchFile& SearchFile::Instance() {
  if (!instance) {
    instance = new SearchFile();
    LOG_INFO("new instance . \n");
  }

  return *instance;
}

void SearchFile::Init() {}

void SearchFile::AddFolder(const std::string& folder) {
  this->search_folder.push_back(folder);
}

void SearchFile::Uninit() {
  delete instance;
  instance = nullptr;

  LOG_INFO("delete instance . \n");
}

bool SearchFile::GetFilePaths(const std::string& file_name,
                              std::vector<std::string>& file_paths) {
  file_paths.clear();
  bool ret = true;
  for (auto& i : this->search_folder) {
    ret &= SearchFiles(i, file_name, file_paths);
  }

  return ret;
}

// 搜索指定文件夹中与指定文件名匹配的文件，并返回文件的所在目录
bool SearchFile::SearchFiles(const std::string& folderPath,
                             const std::string& targetFileName,
                             std::vector<std::string>& filePaths) {
  DIR* dir;
  struct dirent* entry;

  dir = opendir(folderPath.c_str());
  if (dir == nullptr) {
    printf("Failed to open directory: %s ", folderPath.c_str());
    return false;
  }

  while ((entry = readdir(dir)) != nullptr) {
    if (entry->d_type == DT_DIR) {
      // 忽略目录 "." 和 ".."
      if (std::string(entry->d_name) != "." &&
          std::string(entry->d_name) != "..") {
        std::string subFolderPath =
            folderPath + "/" + std::string(entry->d_name);

        if (!SearchFiles(subFolderPath, targetFileName, filePaths))
          return false;
      }
    } else if (entry->d_type == DT_REG) {
      if (std::strcmp(entry->d_name, targetFileName.c_str()) == 0) {
        // std::string filePath = folderPath + "/" +
        // std::string(entry->d_name);
        std::string filePath = folderPath;
        filePaths.push_back(filePath);
      }
    }
  }

  closedir(dir);
}

}  // namespace entry
}  // namespace gomros

