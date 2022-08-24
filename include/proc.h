#ifndef _PROC_H_
#define _PROC_H_

#include "ring.h"
#include "packet.h"
#include "sleep.h"

#include <stdio.h>

void *process_incoming_packets(void *ring);

#endif // _PROC_H_
