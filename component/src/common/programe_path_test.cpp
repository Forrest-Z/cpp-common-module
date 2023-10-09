#include <gtest/gtest.h>
#include "program_path.h"

TEST(common, p_path) {
  printf("-----------test start------------\n");

  {
    std::string a = common::ProgramPath::Get();
    printf("path = %s \n", a.c_str());
  }
}