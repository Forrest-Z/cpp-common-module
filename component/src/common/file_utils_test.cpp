
#include "common/file_utils.h"
#include <gtest/gtest.h>

TEST(common, component_file) {
  printf("-----------test start------------\n");

  std::string filename = "file_test.txt";
  std::string data = "123456abcde&#";

  gomros::common::FileUtils::WriteSmallFile(filename, data);

  std::string read_buf;
  gomros::common::FileUtils::ReadSmallFile(filename, read_buf);

  std::cout << data << std::endl;
  std::cout << read_buf << std::endl;

  ASSERT_EQ(data.size(), read_buf.size());

  for (size_t i = 0; i < data.size(); i++) {
    ASSERT_EQ(data[i], read_buf[i]);
  }

  // app
  std::cout << "append file : " << std::endl;

  gomros::common::FileUtils::AppendFile(filename, data);
  gomros::common::FileUtils::ReadSmallFile(filename, read_buf);

  std::cout << data << std::endl;
  std::cout << read_buf << std::endl;

  ASSERT_EQ(data.size() * 2, read_buf.size());
}
