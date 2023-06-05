
#include "file_utils.h"

#include <fstream>
#include <iostream>
namespace common {

bool file_utils::ReadSmallFile(std::string filename, std::string& buf) {
  auto f = std::ifstream(filename.c_str(), std::ios_base::in);

  if (!f) {
    printf("file not exist . \n");
    return false;
  }

  try {
    // get length of file:
    f.seekg(0, f.end);
    uint32_t length = f.tellg();
    f.seekg(0, f.beg);

    buf.resize(length);
    f.read((char*)buf.data(), length);

    f.close();
    return true;

  } catch (const std::exception& e) {
    printf("%s\n", e.what());
    f.close();
    return false;
  }
}

bool file_utils::WriteSmallFile(std::string filename, std::string& buf) {
  auto f = std::ofstream(filename.c_str(), std::ios_base::out);
  if (!f) {
    printf("file not exist . \n");
    return false;
  }

  f.write(buf.data(), buf.size());

  f.close();
  return true;
}

bool file_utils::AppendFile(std::string filename, std::string& buf) {
  auto f =
      std::ofstream(filename.c_str(), std::ios_base::out | std::ios_base::app);

  if (!f) {
    printf("file not exist . \n");
    return false;
  }
  f.write(buf.data(), buf.size());

  f.close();
  return true;
}

}  // namespace common
