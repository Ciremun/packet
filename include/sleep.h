#ifndef _OS_H_
#define _OS_H_

#ifdef _WIN32
#include <synchapi.h>
#else
#include <unistd.h>
#endif // _WIN32

void sleep_ms(unsigned int ms);

#endif // _OS_H_
