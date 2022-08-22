#ifdef _WIN32

#include "clock.h"

// https://stackoverflow.com/a/38212960
int clock_gettime(int dummy, struct timespec *ct)
{
    (void)dummy;
    static BOOL g_first_time = 1;
    static LARGE_INTEGER g_counts_per_sec;
    LARGE_INTEGER count;

    if (g_first_time)
    {
        g_first_time = 0;

        if (0 == QueryPerformanceFrequency(&g_counts_per_sec))
        {
            g_counts_per_sec.QuadPart = 0;
        }
    }

    if ((NULL == ct) || (g_counts_per_sec.QuadPart <= 0) ||
            (0 == QueryPerformanceCounter(&count)))
    {
        return -1;
    }

    ct->tv_sec = count.QuadPart / g_counts_per_sec.QuadPart;
    ct->tv_nsec = ((count.QuadPart % g_counts_per_sec.QuadPart) * 1E9) / g_counts_per_sec.QuadPart;

    return 0;
}
#endif // _WIN32