#pragma once

#include <iostream>

#define fatal_log(format, ...)        \
  printf("\033[0;31m fatal \033[0m"); \
  printf(format, ##__VA_ARGS__)

#define error_log(format, ...)        \
  printf("\033[0;31m error \033[0m"); \
  printf(format, ##__VA_ARGS__)

#define warning_log(format, ...)      \
  printf("\033[0;31m warning \033[0m"); \
  printf(format, ##__VA_ARGS__)

#define info_log(format, ...)         \
  printf("\033[1;34m info \033[0m"); \
  printf(format, ##__VA_ARGS__)

#define debug_log(format, ...)        \
  printf("\033[1;34m debug \033[0m"); \
  printf(format, ##__VA_ARGS__)
