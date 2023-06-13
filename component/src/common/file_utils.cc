
#include "common/file_utils.h"

#include <fstream>
#include <iostream>

namespace gomros {
namespace common {

bool FileUtils::ReadSmallFile(const std::string& filename, std::string& buf) {
  auto f = std::ifstream(filename.c_str(), std::ios_base::in);
  buf.clear();

  // 文件打开失败
  if (!f) {
    return false;
  }

  try {
    // get length of file:
    f.seekg(0, f.end);
    uint32_t length = f.tellg();
    f.seekg(0, f.beg);

    char context[length];
    f.read(context, length);

    buf.resize(length);
    buf.append(context, length);

    f.close();
    return true;

  } catch (const std::exception& e) {
    f.close();
    return false;
  }
}

bool FileUtils::WriteSmallFile(const std::string& filename, std::string& buf) {
  auto f = std::ofstream(filename.c_str(), std::ios_base::out);
  buf.clear();

  // 文件打开失败
  if (!f) {
    return false;
  }

  f.write(buf.data(), buf.size());

  f.close();
  return true;
}

bool FileUtils::AppendFile(const std::string& filename, std::string& buf) {
  auto f =
      std::ofstream(filename.c_str(), std::ios_base::out | std::ios_base::app);
  buf.clear();

  // 文件打开失败
  if (!f) {
    return false;
  }
  f.write(buf.data(), buf.size());

  f.close();
  return true;
}

}  // namespace common
}  // namespace gomros

