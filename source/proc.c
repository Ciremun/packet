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
            Packet *packet = (Packet *)packets_ring->data[i];
            if (packet == 0)
                continue;
            if (packet->state == PKT_CREATED)
            {
                if (verify_packet_md5(&packet->array, packet->hash))
                    printf("md5 verification PASS!\n");
                else
                    printf("md5 verification FAIL!\n");
                packet->state = PKT_PROCESSED;
            }
        }
        unlock_mutex(packets_mutex);
        sleep_ms(15);
    }
    return 0;
}
