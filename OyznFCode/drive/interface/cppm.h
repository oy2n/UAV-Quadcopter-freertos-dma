#ifndef __CPPM_H
#define __CPPM_H

#include "sys.h"

void cppmInit(void);
bool cppmIsAvailible(void);
void cppmClearQueue(void);
int cppmGetTimestamp(uint16_t *timestamp);

#endif


