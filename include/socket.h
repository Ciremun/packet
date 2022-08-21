#ifndef _SOCKET_H_
#define _SOCKET_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#define close closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif // _WIN32

#include <time.h>
#include <string.h>
#include <stdio.h>

#endif // _SOCKET_H_
