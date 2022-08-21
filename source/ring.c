#include "ring.h"

Ring ring_init(void *data, size_t size)
{
    Ring ring;
    ring.index = 0;
    ring.data = data;
    ring.size = size;
    return ring;
}

void ring_write(Ring *ring, void *item)
{
    if (ring->index == ring->size)
        ring->index = 0;
    ring->data[ring->index++] = item;
}
