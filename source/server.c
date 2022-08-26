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

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    Packet packet_info;
    int bytes_read = 0;
    uintptr_t packets[16] = {0};
    Ring ring = ring_init(packets, 16);

    PacketProc packet_proc;
    packet_proc.ring = &ring;
    packet_proc.mutex = create_mutex();
    pkt_thread_t packets_thread = create_thread(process_incoming_packets, &packet_proc);

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        for (int i = 0; i < 2000; ++i)
        {
            if ((bytes_read = recv(connfd, (char *)&packet_info, PKT_INFO_SIZE, MSG_WAITALL)) > 0)
            {
                if (bytes_read != PKT_INFO_SIZE)
                    goto error;
                if (!(600 <= packet_info.array.size && packet_info.array.size <= 1600))
                {
                    SOCK_ERROR(PKT_SIZE_ERROR);
                    goto error;
                }
                Packet *packet = (Packet *)malloc(PKT_SIZE(packet_info.array.size));
                memcpy(packet, &packet_info, PKT_INFO_SIZE);
                if ((bytes_read = recv(connfd, (char *)&packet->array.data, packet->array.size * sizeof(int16_t), MSG_WAITALL)) > 0)
                {
                    if (bytes_read != packet->array.size * sizeof(int16_t))
                        goto error;
                    // printf("packet: %zu, %s.%ld, %d\n", packet->id, strtok(ctime(&packet->date.tv_sec), "\n"), packet->date.tv_nsec, packet->state);
                    lock_mutex(packet_proc.mutex);
                    ring_write(&ring, packet);
                    unlock_mutex(packet_proc.mutex);
                }
                else if (bytes_read < 0)
                {
                    SOCK_ERROR(PKT_RECV_ERROR);
                    goto error;
                }
            }
            else if (bytes_read < 0)
            {
                SOCK_ERROR(PKT_RECV_ERROR);
                goto error;
            }
        }
error:
        close(connfd);
        sleep_ms(10);
    }

    join_thread(packets_thread);
    delete_mutex(packet_proc.mutex);

    return 0;
}
