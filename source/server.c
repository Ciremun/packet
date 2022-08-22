#include "server.h"

int main(void)
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
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[512];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(sendBuff, 0, sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    Packet received_packet;
    int n = 0;

    int packets[16] = {0};
    Ring ring = ring_init(packets, 16);

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        ticks = time(NULL);

        while ((n = recv(connfd, (char *)&received_packet, sizeof(Packet), MSG_WAITALL)) > 0)
        {
            printf("receiving data: %d bytes\n", n);
            printf("packet: %zu, %s.%ld, %d\n", received_packet.id, strtok(ctime(&received_packet.date.tv_sec), "\n"), received_packet.date.tv_nsec, received_packet.state);
            Packet *packet = (Packet *)malloc(sizeof(Packet));
            memcpy(packet, &received_packet, sizeof(Packet));
            ring_write(&ring, packet);
        }

        if (n < 0)
        {
            SOCK_ERROR(PKT_RECV_ERROR);
        }

        close(connfd);
        // sleep_ms(1);
    }
    return 0;
}
