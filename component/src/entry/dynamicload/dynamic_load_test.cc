
#include "dynamic_load.h"
#include <gtest/gtest.h>

TEST(entry, dynamic_load) {
  std::string ld_path =
      "/root/tong/git_repo/cpp-common-module/component/test_data/"
      "libdynamic_load_test.so";
  gomros::entry::ComponentFunc func_list;

  bool ret = gomros::entry::DynamicLoad::LoadEntryFunc(ld_path, &func_list);

  EXPECT_TRUE(ret);

  func_list.init(nullptr);
  func_list.uninit(nullptr);
}