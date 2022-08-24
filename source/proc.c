#include "proc.h"

void *process_incoming_packets(void *packet_proc)
{
    PacketProc *pp = (PacketProc *)packet_proc;
    Ring *packets_ring = pp->ring;
    pkt_mutex_t packets_mutex = pp->mutex;
    while (1)
    {
        lock_mutex(packets_mutex);
        for (size_t i = 0; i < packets_ring->size; ++i)
        {
            Packet *packet = (Packet *)packets_ring->data[i];
            if (packet == 0)
                continue;
            if (packet->state == PKT_CREATED)
            {
                printf("found packet with created state!\n");
                packet->state = PKT_PROCESSED;
            }
        }
        unlock_mutex(packets_mutex);
        sleep_ms(15);
    }
    return 0;
}
