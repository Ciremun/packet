#include "error.h"

void print_sock_error(const char *error_name, const char *file, int line)
{
#ifndef NDEBUG

#ifdef _WIN32
    fprintf(stderr, "%s:%d - %s: %ld", file, line, error_name, WSAGetLastError());
#else
    fprintf(stderr, "%s:%d - %s: %s", file, line, error_name, strerror(errno));
#endif // _WIN32

#else

#ifdef _WIN32
    fprintf(stderr, "%s: %ld", error_name, WSAGetLastError());
#else
    fprintf(stderr, "%s: %s", error_name, strerror(errno));
#endif // _WIN32

#endif // NDEBUG
}
