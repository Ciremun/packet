#include "os.h"

void sleep_seconds(unsigned int seconds)
{
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif // _WIN32
}
