

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
  static SearchFile& Instance();

  void Init();

  void Uninit();

  /**
   * @brief 添加搜索目录，先添加的目录优先搜索 （gomros安装路径 ， project路径
   * ， 数据目录 中搜索指定文件）
   *
   * @param folder
   */
  void AddFolder(const std::string& folder);
  /**
   * @brief Get the File Paths object
   *
   * @param file_name 文件名， eg: "product.xml"
   * @param file_paths 返回文件目录路径列表,按优先级排列，eg:
   * {"/opt/gomros/run/ProductA","/opt/gomros/run/ProductA/config"}
   * @return true 成功
   * @return false 失败
   */
  bool GetFilePaths(const std::string& file_name,
                    std::vector<std::string>& file_paths);

 private:
  // 搜索指定文件夹中与指定文件名匹配的文件，并返回文件的所在目录
  bool SearchFiles(const std::string& folderPath,
                   const std::string& targetFileName,
                   std::vector<std::string>& filePaths);

  static SearchFile* instance;
  std::vector<std::string> search_folder;
};

}  // namespace entry
}  // namespace gomros
