#include "include/common/backtrace.h"

#include <execinfo.h>
#include <signal.h>  // ::signal, ::raise
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace common {

static const size_t stack_buffer_size_ = UINT16_MAX;
static void* stack_buffer_[stack_buffer_size_];
static size_t stack_nptrs_ = 0;

static void ErrorPrintf(std::string s) {
  std::ofstream o_file;
  o_file.open("error.log", std::ios::app);
  o_file << s << std::endl;
  o_file.close();
}

static void ErrorHandle(void) {
  std::string s =
      "backtrace() returned " + std::to_string(stack_nptrs_) + " addresses";
  ErrorPrintf(s);

  /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
     would produce similar output to the following: */

  auto strings = backtrace_symbols(stack_buffer_, stack_nptrs_);
  if (strings == NULL) {
    printf("backtrace_symbols");
    exit(EXIT_FAILURE);
  }

  for (int j = 0; j < stack_nptrs_; j++) {
    // printf("%s\n", strings[j]);
    s = strings[j];
    ErrorPrintf(s);
  }

  free(strings);
}

void CoredumpBacktrace(int signum) {
  // write stack to buffer
  stack_nptrs_ = backtrace(stack_buffer_, sizeof(stack_buffer_));

  // 写入日期
  auto re = system("date > error.log");

  std::string s = "dump_backtrace on signal : " + std::to_string(signum);
  ErrorPrintf(s);
  ErrorHandle();

  // 设置成默认处理，并重新生成信号
  signal(signum, SIG_DFL);
  raise(signum);
}

void ErrorBacktraceRegister(void) {
  // register signal
  ::signal(SIGSEGV, CoredumpBacktrace);  // segmentation violation
  ::signal(SIGABRT, CoredumpBacktrace);  // abort program (formerly SIGIOT)
  ::signal(SIGINT, CoredumpBacktrace);   // ctrl + c
}

void AddListeningSignal(int sig) {
  ::signal(sig, CoredumpBacktrace);  // ctrl + c
}

}  // namespace common
