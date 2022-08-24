#ifndef _PACKET_H_
#define _PACKET_H_

#include <stddef.h>
#include <time.h>
#include <stdint.h>

#include "clock.h"

#define PKT_SIZE(packet) (offsetof(Packet, array) + sizeof(size_t) + packet.array.size * sizeof(int16_t))

typedef enum
{
    PKT_ERROR = 0,
    PKT_CREATED,
    PKT_PROCESSED,
} PacketState;

typedef struct
{
    size_t size;
    int16_t data[];
} PacketData;

typedef struct
{
    size_t id;
    struct timespec date;
    PacketState state;
    PacketData array;
} Packet;

#endif // _PACKET_H_
