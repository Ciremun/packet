#ifdef _WIN32

#include "clock.h"

// https://stackoverflow.com/a/38212960
int clock_gettime(int f, struct timespec *ct)
{
    (void)f;
    __int64 wintime;
    GetSystemTimeAsFileTime((FILETIME*)&wintime);
    wintime -= (uint64_t)116444736000000000;
    ct->tv_sec  =wintime / (uint64_t)10000000;
    ct->tv_nsec =wintime % (uint64_t)10000000 *100;
    return 0;
}
#endif // _WIN32
