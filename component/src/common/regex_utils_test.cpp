#include "regex_utils.h"
#include <gtest/gtest.h>

TEST(common, regex_utils) {
  printf("-----------test start------------\n");

  {
    std::string input = "----------X86_64--------------";
    std::string pattern = "x86_64";

    auto ret = gomros::common::regex_utils::Search(pattern, input);

    printf("find x86_64 , ret = %d \n", ret);
  }

  {
    std::string input = "----------arm64--------------";
    std::string pattern = "arm64";

    auto ret = gomros::common::regex_utils::Search(pattern, input);

    printf("find arm64 , ret = %d \n", ret);

 auto ret2 = gomros::common::regex_utils::Search("x86_64", input);
    EXPECT_FALSE(ret2);
    printf("find x86_64 in arm64 string , ret2 = %d \n", ret2);
  }
}