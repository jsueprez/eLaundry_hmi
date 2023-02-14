#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifdef NDEBUG
#define wDebug(FORMAT, ...)
#define wTrace()
#define wCounter(NAME)
#else
#define wDebug(FORMAT, ...)   printf(ANSI_COLOR_RESET  FORMAT ANSI_COLOR_RESET, ##__VA_ARGS__);
#define wTrace()              printf(ANSI_COLOR_RESET "Line %04d | Thread %06ld: %s, %s\n" ANSI_COLOR_RESET, __LINE__, syscall(__NR_gettid), __func__, __FILE__);
#define wCounter(NAME)        { static int NAME = 0; ++NAME; printf(ANSI_COLOR_MAGENTA "Counter " #NAME ": %d\n" ANSI_COLOR_RESET, NAME); }
#endif

#define wInfo(FORMAT, ...)    printf(ANSI_COLOR_CYAN   FORMAT ANSI_COLOR_RESET, ##__VA_ARGS__);
#define wWarning(FORMAT, ...) printf(ANSI_COLOR_YELLOW FORMAT ANSI_COLOR_RESET, ##__VA_ARGS__);
#define wError(FORMAT, ...)   printf(ANSI_COLOR_RED    FORMAT ANSI_COLOR_RESET, ##__VA_ARGS__);

#define wTryCatch(FUNC)       try { FUNC; } catch (std::exception &e) { wError("Line %04d: %s, %s\n", __LINE__, __func__, e.what()); }
