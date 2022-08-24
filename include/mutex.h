#ifndef _MUTEX_H_
#define _MUTEX_H_

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif // _WIN32

#include <stdlib.h>

typedef void* pkt_mutex_t;

pkt_mutex_t create_mutex();
void lock_mutex(pkt_mutex_t m);
void unlock_mutex(pkt_mutex_t m);
void delete_mutex(pkt_mutex_t m);

#endif //  _MUTEX_H_
