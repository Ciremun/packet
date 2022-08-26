#ifndef _PACKET_H_
#define _PACKET_H_

#include <stddef.h>
#include <time.h>
#include <stdint.h>

#include "clock.h"

#define PKT_INFO_SIZE (offsetof(Packet, array) + sizeof(size_t))
#define PKT_SIZE(array_size) (PKT_INFO_SIZE + array_size * sizeof(int16_t))

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
    uint8_t hash[16];
    PacketData array;
} Packet;

#endif // _PACKET_H_
