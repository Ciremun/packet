#ifndef _PROC_H_
#define _PROC_H_

#include "ring.h"
#include "packet.h"
#include "sleep.h"
#include "mutex.h"

#include <stdio.h>

typedef struct
{
    Ring *ring;
    pkt_mutex_t mutex;
} PacketProc;

void *process_incoming_packets(void *packet_proc);

#endif // _PROC_H_
