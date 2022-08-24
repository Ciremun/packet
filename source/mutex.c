#include "mutex.h"

pkt_mutex_t create_mutex()
{
#ifdef _WIN32
    return CreateMutex(0, 0, 0);
#else
	pthread_mutexattr_t mta;
	og_mutex_t r = malloc(sizeof(pthread_mutex_t));
	if (!r)
        return 0;
	pthread_mutexattr_init(&mta);
	pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init((pthread_mutex_t *)r, &mta);
	return r;
#endif // _WIN32
}

void lock_mutex(pkt_mutex_t m)
{
#ifdef _WIN32
    WaitForSingleObject(m, INFINITE);
#else
    if (!m)
	    return;
	pthread_mutex_lock((pthread_mutex_t*)m);
#endif // _WIN32
}

void unlock_mutex(pkt_mutex_t m)
{
#ifdef _WIN32
    ReleaseMutex(m);
#else
    if (!m)
		return;
	pthread_mutex_unlock((pthread_mutex_t*)m);
#endif // _WIN32
}

void delete_mutex(pkt_mutex_t m)
{
#ifdef _WIN32
    CloseHandle(m);
#else
    if (!m)
		return;
	pthread_mutex_destroy((pthread_mutex_t*)m);
	free(m);
#endif // _WIN32
}
