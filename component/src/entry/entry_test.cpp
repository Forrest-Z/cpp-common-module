#include <gtest/gtest.h>

static bool running_flag = true;

#include "entry.h"

TEST(entry, entry_product) {
  int argc = 2;
  char** argv;
  argv[0] = "gomros";
  argv[1] = "-product";
  Entry(argc, argv);
}