#ifndef _THREAD_H_
#define _THREAD_H_

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <stdlib.h>
#endif // _WIN32

typedef void *pkt_thread_t;

pkt_thread_t create_thread(void *(routine)(void *), void *parameter);
void *join_thread(pkt_thread_t t);

#endif // _THREAD_H_
