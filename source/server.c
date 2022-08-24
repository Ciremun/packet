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

    Packet received_packet;
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

        while ((bytes_read = recv(connfd, (char *)&received_packet, sizeof(Packet), MSG_WAITALL)) > 0)
        {
            printf("receiving data: %d bytes\n", bytes_read);
            printf("packet: %zu, %s.%ld, %d\n", received_packet.id, strtok(ctime(&received_packet.date.tv_sec), "\n"), received_packet.date.tv_nsec, received_packet.state);
            Packet *packet = (Packet *)malloc(sizeof(Packet));
            memcpy(packet, &received_packet, sizeof(Packet));
            lock_mutex(packet_proc.mutex);
            ring_write(&ring, packet);
            unlock_mutex(packet_proc.mutex);
        }

        if (bytes_read < 0)
        {
            SOCK_ERROR(PKT_RECV_ERROR);
        }

        close(connfd);
        sleep_ms(10);
    }

    join_thread(packets_thread);
    delete_mutex(packet_proc.mutex);

    return 0;
}
