#include "proc.h"

void *process_incoming_packets(void *ring)
{
    Ring *packets_ring = (Ring *)ring;
    while (1)
    {
        for (size_t i = 0; i < packets_ring->size; ++i)
        {
            Packet *packet = (Packet *)packets_ring->data[i];
            if (packet == 0)
            {
                printf("empty ring slot!\n");
                continue;
            }
            if (packet->state == PKT_CREATED)
            {
                printf("found packet with created state!\n");
                packet->state = PKT_PROCESSED;
            }
            else
            {
                printf("found packet with %d state!\n", packet->state);
            }
        }
        sleep_ms(3000);
    }
    return 0;
}
