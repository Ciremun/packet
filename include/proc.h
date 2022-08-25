#ifndef _PROC_H_
#define _PROC_H_

#include "ring.h"
#include "packet.h"
#include "sleep.h"
#include "mutex.h"
#include "md5.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct
{
    Ring *ring;
    pkt_mutex_t mutex;
} PacketProc;

int verify_packet_md5(PacketData *array, uint8_t *hash);
void *process_incoming_packets(void *packet_proc);

#endif // _PROC_H_
