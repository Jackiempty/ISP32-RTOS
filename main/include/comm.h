#ifndef _COMM_
#define _COMM_

#include <stddef.h>
#include <stdint.h>

#include "bsp.h"

/* Waited to be replaced */
#include "ra01s.h"

void comm_task(void*);
uint8_t* comm_fetch();
size_t comm_len();

#endif