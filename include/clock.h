#ifdef _WIN32

#include <windows.h>

#include <stdint.h>
#include <time.h>

#define CLOCK_MONOTONIC_RAW 0

int clock_gettime(int dummy, struct timespec *ct);
#endif // _WIN32