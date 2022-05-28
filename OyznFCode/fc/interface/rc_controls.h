#ifndef __RC_CONTROL_H
#define __RC_CONTROL_H
#include "sys.h"
#include "rx.h"

typedef enum 
{
    THROTTLE_LOW = 0,
    THROTTLE_HIGH
} throttleStatus_e;

typedef enum 
{
    NOT_CENTERED = 0,
    CENTERED
} rollPitchStatus_e;

typedef enum 
{
    ROL_LO = (1 << (2 * ROLL)),
    ROL_CE = (3 << (2 * ROLL)),
    ROL_HI = (2 << (2 * ROLL)),

    PIT_LO = (1 << (2 * PITCH)),
    PIT_CE = (3 << (2 * PITCH)),
    PIT_HI = (2 << (2 * PITCH)),

    THR_LO = (1 << (2 * THROTTLE)),
    THR_CE = (3 << (2 * THROTTLE)),
    THR_HI = (2 << (2 * THROTTLE)),
	
	YAW_LO = (1 << (2 * YAW)),
    YAW_CE = (3 << (2 * YAW)),
    YAW_HI = (2 << (2 * YAW)),
} stickPositions_e;

typedef enum 
{
	AUX_LO = 0,
    AUX_CE = 1,
    AUX_HI = 2,
} auxPositions_e;

stickPositions_e getRcStickPositions(void);
bool checkStickPosition(stickPositions_e stickPos);

bool areSticksInApModePosition(uint16_t ap_mode);
throttleStatus_e calculateThrottleStatus(void);
rollPitchStatus_e calculateRollPitchCenterStatus(void);
void processRcStickPositions(void);

int32_t getRcStickDeflection(int32_t axis, uint16_t midrc);
void processRcAUXPositions(void);

#endif
