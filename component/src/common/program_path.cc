#include "program_path.h"

#include <cstring>

#include <unistd.h>

std::string common::ProgramPath::Get() {
  char szBuf[UINT16_MAX];
  char szPath[UINT16_MAX];

  memset(szBuf, 0x00, sizeof(szBuf));
  memset(szPath, 0x00, sizeof(szPath));

  { auto i = getcwd(szBuf, sizeof(szBuf) - 1); }
  printf("buf:%s\n", szBuf);

  int ret = readlink("/proc/self/exe", szPath, sizeof(szPath) - 1);
  printf("ret:%d\n", ret);
  printf("path:%s\n", szPath);

  if (ret == -1) {
    return "";
  }

  return std::string(szPath, ret);
}