#pragma once

#include <iostream>
#include <cstring>

#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define PRINT_DEFAULT printf("%s %s %d ", __FILENAME__, __FUNCTION__, __LINE__);

#define LOG_FATAL(format, ...)        \
  printf("\033[0;31m fatal \033[0m"); \
  PRINT_DEFAULT                       \
  printf(format, ##__VA_ARGS__);      \
  printf("\n")

#define LOG_ERROR(format, ...)        \
  printf("\033[0;31m error \033[0m"); \
  PRINT_DEFAULT                       \
  printf(format, ##__VA_ARGS__);      \
  printf("\n")

#define LOG_WARN(format, ...)           \
  printf("\033[0;31m warning \033[0m"); \
  PRINT_DEFAULT                         \
  printf(format, ##__VA_ARGS__);        \
  printf("\n")

#define LOG_INFO(format, ...)        \
  printf("\033[1;34m info \033[0m"); \
  PRINT_DEFAULT                      \
  printf(format, ##__VA_ARGS__);     \
  printf("\n")

#define LOG_DEBUG(format, ...)        \
  printf("\033[1;34m debug \033[0m"); \
  PRINT_DEFAULT                       \
  printf(format, ##__VA_ARGS__);      \
  printf("\n")
