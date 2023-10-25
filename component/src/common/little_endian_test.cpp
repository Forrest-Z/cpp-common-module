#include "little_endian.h"

#include <gtest/gtest.h>

#include <sstream>

std::string char_to_hex(uint8_t c) {
  char buffer[5];
  sprintf(buffer, "%02X", c);
  return std::string(buffer);
}

std::string to_string(const std::vector<uint8_t> &data) {
  std::stringstream ss;
  ss << std::hex;
  for (auto &i : data) {
    ss << char_to_hex(i) << " ";
  }
  return ss.str();
}

template <class T>
bool ReadWriteTest(T data) {
  std::cout << "---------------------------------------" << std::endl;
  std::vector<uint8_t> buf = {0, 0, 0, 0};

  std::cout << "buf: " << to_string(buf) << std::endl;
  {
    gomros::common::LittleEndianWrite<T>(buf.data(), data);

    std::cout << "buf: " << to_string(buf) << std::endl;
  }

  T data2 = gomros::common::LittleEndianRead<T>(buf.data());

  std::cout << "data: " << (T)data << " , data2: " << (T)data2 << std::endl;

  return (data2 == data);
}

TEST(common, little_endian) {
  printf("-----------test start------------\n");

  EXPECT_TRUE(ReadWriteTest((int32_t)1000));
  EXPECT_TRUE(ReadWriteTest((int32_t)-1000));

  EXPECT_TRUE(ReadWriteTest((int16_t)100));
  EXPECT_TRUE(ReadWriteTest((int16_t)-100));

  EXPECT_TRUE(ReadWriteTest((uint32_t)100));
  EXPECT_TRUE(ReadWriteTest((uint32_t)-100));
}
