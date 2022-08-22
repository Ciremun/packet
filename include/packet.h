#include <stddef.h>

typedef enum
{
    PKT_ERROR = 0,
    PKT_CREATED,
    PKT_PROCESSED,
} PacketState;

typedef struct
{
    size_t id;
    long date;
    PacketState state;
    int data[1024];
} Packet;
