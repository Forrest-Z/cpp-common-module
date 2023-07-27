#pragma once
#include <stdio.h>
#include <cstring>

#define MY_LOG_DEBUG 1

// printf("DEBUG %s  %d  %s",__FILENAME__,__LINE__,__FUNCTION__);  \
#define __FILENAME__ \
(strrchr(__FILE__,'/')?(strrchr(__FILE,'/')+1):__FILE__)

#if MY_LOG_DEBUG
#ifndef MY_LOGDBG
#define MY_LOGDBG(fmt,...)    \
printf(fmt,##__VA_ARGS__);
#endif
#else
#define MY_LOGDBG(fmt,...)   ((void)0)
#endif