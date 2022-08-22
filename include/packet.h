#include <stddef.h>
#include <time.h>

#include "clock.h"

typedef enum
{
    PKT_ERROR = 0,
    PKT_CREATED,
    PKT_PROCESSED,
} PacketState;

typedef struct
{
    size_t id;
    struct timespec date;
    PacketState state;
    int data[1024];
} Packet;
