#include <gtest/gtest.h>

static bool running_flag = true;

#include "entry.h"

TEST(entry, entry_product) {
  int argc = 2;
  char** argv = (char**)malloc(3 * sizeof(char*));
  argv[0] = (char*)"gomros";
  argv[1] = (char*)"-product";
  Entry(argc, argv);

  free(argv);
}

TEST(entry, entry_process) {
  int argc = 3;
  char** argv = (char**)malloc(3 * sizeof(char*));

  argv[0] = (char*)"gomros";
  argv[1] = (char*)"-process";
  argv[2] = (char*)"process1";
  Entry(argc, argv);

    free(argv);
}