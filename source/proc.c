#include "proc.h"

#include <stdio.h>

void *process_incoming_packets(void *ring)
{
    Ring *ring_ = (Ring *)ring;
    printf("processing incoming packets!\n");
    return 0;
}
