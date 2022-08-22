#ifndef _ERROR_H_
#define _ERROR_H_

#include "socket.h"

#define PKT_SOCK_ERROR "PKT_SOCK_ERROR"
#define PKT_INET_ERROR "PKT_INET_ERROR"
#define PKT_CONN_ERROR "PKT_CONN_ERROR"
#define PKT_RECV_ERROR "PKT_RECV_ERROR"
#define PKT_SEND_ERROR "PKT_SEND_ERROR"
#define PKT_SOME_ERROR "PKT_SOME_ERROR"

#define SOCK_ERROR(error_name) print_sock_error(error_name, __FILE__, __LINE__)

void print_sock_error(const char *error_name, const char *file, int line);

#endif // _ERROR_H_
