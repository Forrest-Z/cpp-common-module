
#include "include/common/HexConverter.h"

#include <gtest/gtest.h>

TEST(HexConverter_test, hex_to_chararray) {
  printf("-----------test start------------\n");

  std::string hex = "0123456789ABCDEF";
  std::vector<char> chararray;
  std::vector<unsigned char> compare = {0x01, 0x23, 0x45, 0x67,
                                        0x89, 0xAB, 0XCD, 0XEF};
  common::HexToCharArray(hex, &chararray);

  ASSERT_EQ(chararray.size(), compare.size());

  for (size_t i = 0; i < chararray.size(); i++) {
    EXPECT_EQ(chararray[i], (char)compare[i]);
  }
}

TEST(HexConverter_test, chararray_to_hex) {
  printf("-----------test start------------\n");

  std::string compare = "0123456789ABCDEF";
  std::vector<char> chararray = {
      0x01, 0x23, 0x45, 0x67, (char)0x89, (char)0xAB, (char)0XCD, (char)0XEF};
  std::string out;

  common::CharArrayToHex(chararray, &out);

  ASSERT_EQ(compare.size(), out.size());

  for (size_t i = 0; i < compare.size(); i++) {
    EXPECT_EQ(compare[i], (char)out[i]);
  }
}