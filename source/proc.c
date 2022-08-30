#include "proc.h"

int verify_packet_md5(PacketData *array, uint8_t *hash)
{
    MD5Context ctx;
    md5Init(&ctx);
    md5Update(&ctx, (uint8_t *)array->data, array->size);
    md5Finalize(&ctx);
    return memcmp(ctx.digest, hash, 16) == 0;
}

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
            sleep_ms(15);
            Packet *packet = (Packet *)packets_ring->data[i];
            if (packet && packet->state == PKT_CREATED)
            {
                printf("Processed: %zu %s.%ld %s\n", packet->id,
                            strtok(ctime(&packet->date.tv_sec), "\n"), packet->date.tv_nsec,
                            verify_packet_md5(&packet->array, packet->hash) ? "PASS" : "FAIL");
                packets_ring->data[i] = 0;
                free(packet);
            }
        }
        unlock_mutex(packets_mutex);
    }
    return 0;
}
