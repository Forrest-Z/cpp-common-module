
#pragma once
namespace common {

/**
 * @brief backtrace程序崩溃时，程序的堆栈信息 \n
 *		 并将堆栈信息存放再error.log中，并记录程序退出时间  \n
 *		 error.log 中信息如下所示： \n
 *
 *		 Fri Jun 17 15:26:38 CST 2022 \n
 *		 dump_backtrace on signal: 8 \n
 *		 backtrace() returned 8 addresses \n
 *		 ./main(+0x39d7) [0x7fe1ff4039d7] \n
 *		 ./main(+0x3d0b) [0x7fe1ff403d0b] \n
 *		 /lib/x86_64-linux-gnu/libc.so.6(+0x3ef10) [0x7fe1fe46ef10] \n
 *		 ./main(+0x47f2) [0x7fe1ff4047f2] \n
 *		 ./main(+0x484c) [0x7fe1ff40484c] \n
 *		 ./main(+0x37fe) [0x7fe1ff4037fe] \n
 *		 /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7)
 *[0x7fe1fe451c87] \n
 *		 ./main(+0x36ea) [0x7fe1ff4036ea] \n
 *
 * --------------------------------------------------------
 *
 *	通过shell指令 addr2line -e ./main 0x47f2 -sfC \n
 *
 *   可获取以下信息: \n
 *	test_sig_fpe() \n
 *	error_backtrace_test.cpp:38 \n
 *
 *	通过每个地址对应的函数，可以去判断程序是从哪个模块出现故障退出的。
 *
 *	备注：需要在cmake中 add_compile_options 加入 -rdynamic 条件。
 *
 */
void ErrorBacktraceRegister(void);

/**
 * @brief 添加监听的信号 ，如SIGBUS，参考Linux系统允许监听的信号
 * 
 * @param sig 新加监听的信号
 */
void AddListeningSignal(int sig);

}  // namespace common
