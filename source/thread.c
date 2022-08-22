#include "thread.h"

pkt_thread_t create_thread(void *(routine)(void *), void *parameter)
{
#ifdef _WIN32
    return (pkt_thread_t)CreateThread(0, 0, (LPTHREAD_START_ROUTINE)routine, parameter, 0, 0);
#else
    pthread_t *ret = (pthread_t *)malloc(sizeof(pthread_t));
    if (!ret)
        return 0;
    int r = pthread_create(ret, 0, routine, parameter);
    if (r)
    {
        free(ret);
        return 0;
    }
    return (pkt_thread_t)ret;
#endif // _WIN32
}

void *join_thread(pkt_thread_t t)
{
#ifdef _WIN32
    WaitForSingleObject(t, INFINITE);
    CloseHandle(t);
    return 0;
#else
    void *retval;
    if (!t)
    {
        return 0;
    }
    pthread_join(*(pthread_t *)t, &retval);
    free(t);
    return retval;
#endif // _WIN32
}
