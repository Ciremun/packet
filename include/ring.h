#ifndef _RING_H_
#define _RING_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    void **data;
    size_t size;
    size_t index;
} Ring;

Ring ring_init(void *data, size_t size);
void ring_write(Ring *ring, void *item);

#endif // _RING_H_
