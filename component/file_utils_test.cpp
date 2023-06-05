
#include "file_utils.h"
#include <gtest/gtest.h>

TEST(common, component_file) {
  printf("-----------test start------------\n");

  std::string filename = "file_test.txt";
  std::string data = "123456abcde&#";

  common::file_utils::WriteSmallFile(filename, data);

  std::string read_buf;
  common::file_utils::ReadSmallFile(filename, read_buf);

  std::cout << data << std::endl;
  std::cout << read_buf << std::endl;

  ASSERT_EQ(data.size(), read_buf.size());

  for (size_t i = 0; i < data.size(); i++) {
    ASSERT_EQ(data[i], read_buf[i]);
  }

  // app
  std::cout << "append file : " << std::endl;

  common::file_utils::AppendFile(filename, data);
  common::file_utils::ReadSmallFile(filename, read_buf);

  std::cout << data << std::endl;
  std::cout << read_buf << std::endl;

  ASSERT_EQ(data.size() * 2, read_buf.size());
}
