#ifndef __LED_STRIP_H__
#define __LED_STRIP_H__
#include "sys.h"


void ledStripInit(void);
void ledStripON(void);
void ledStripOFF(void);
void ledstripTask(void *param);

#endif

