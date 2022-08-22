#include "error.h"

void print_sock_error(const char *error_name, const char *file, int line)
{
#ifndef NDEBUG

#ifdef _WIN32
    fprintf(stderr, "%s:%d - %s: %ld\n", file, line, error_name, WSAGetLastError());
#else
    fprintf(stderr, "%s:%d - %s: %s\n", file, line, error_name, strerror(errno));
#endif // _WIN32

#else

#ifdef _WIN32
    fprintf(stderr, "%s: %ld\n", error_name, WSAGetLastError());
#else
    fprintf(stderr, "%s: %s\n", error_name, strerror(errno));
#endif // _WIN32

#endif // NDEBUG
}
