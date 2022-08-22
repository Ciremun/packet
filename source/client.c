#include "client.h"

int main(int argc, char **argv)
{
#ifdef _WIN32
    WSADATA wsaData;
    int wsa = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsa != 0)
    {
        fprintf(stderr, "WSAStartup failed with error: %d", wsa);
        return 1;
    }
#endif
    int sockfd = 0, n = 0;
    char recvBuff[512];
    struct sockaddr_in serv_addr;

    if (argc != 2)
    {
        printf("Usage: %s <ip of server>\n", argv[0]);
        return 1;
    }

    memset(recvBuff, 0, sizeof(recvBuff));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        SOCK_ERROR(PKT_SOCK_ERROR);
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        SOCK_ERROR(PKT_INET_ERROR);
        return 1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        SOCK_ERROR(PKT_CONN_ERROR);
        return 1;
    }

    Packet packet;
    packet.id = 1;
    packet.state = PKT_CREATED;

    struct timespec date;
    clock_gettime(CLOCK_MONOTONIC_RAW, &date);
    packet.date = date;

    printf("ctime: %s\n", ctime(&date.tv_sec));

    srand(time(NULL));
    for (int16_t i = 0; i < 1024; ++i)
        packet.data[i] = rand();

    send(sockfd, (const char *)&packet, sizeof(Packet), 0);

    close(sockfd);
    return 0;
}
