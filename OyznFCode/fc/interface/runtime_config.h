#ifndef __RUNTIME_CONFIG_H
#define __RUNTIME_CONFIG_H
#include "sys.h"

//解锁标志位
typedef enum 
{
    ARMED                                           = (1 << 1),
    WAS_EVER_ARMED                                  = (1 << 2),
    ARMING_DISABLED_NOT_LEVEL                       = (1 << 3),
    ARMING_DISABLED_SENSORS_CALIBRATING             = (1 << 4),
    ARMING_DISABLED_COMPASS_NOT_CALIBRATED          = (1 << 5),
    ARMING_DISABLED_ACCELEROMETER_NOT_CALIBRATED    = (1 << 6),
    ARMING_DISABLED_HARDWARE_FAILURE                = (1 << 7),
	ARMING_DISABLED_FLASH_WRITING                   = (1 << 8),
	ARMING_DISABLED_PID_BYPASS			            = (1 << 9),
	
    ARMING_DISABLED_ALL_FLAGS                       = (ARMING_DISABLED_NOT_LEVEL | ARMING_DISABLED_SENSORS_CALIBRATING | ARMING_DISABLED_COMPASS_NOT_CALIBRATED | 
                                                       ARMING_DISABLED_ACCELEROMETER_NOT_CALIBRATED | ARMING_DISABLED_HARDWARE_FAILURE | ARMING_DISABLED_FLASH_WRITING |
													   ARMING_DISABLED_PID_BYPASS
													   )
} armingFlag_e;
extern uint32_t armingFlags;

#define isArmingDisabled()          (armingFlags & (ARMING_DISABLED_ALL_FLAGS))
#define DISABLE_ARMING_FLAG(mask)   (armingFlags &= ~(mask))
#define ENABLE_ARMING_FLAG(mask)    (armingFlags |= (mask))
#define ARMING_FLAG(mask)           (armingFlags & (mask))


//飞行模式标志位
typedef enum 
{
	ANGLE_MODE        = (1 << 0),
	ACRO_MODE         = (1 << 1),
	HEADFREE_MODE     = (1 << 2),
	NAV_ALTHOLD_MODE  = (1 << 3),
	NAV_RTH_MODE      = (1 << 4),
	NAV_POSHOLD_MODE  = (1 << 5),
	NAV_LAUNCH_MODE   = (1 << 7),
	FAILSAFE_MODE     = (1 << 8),
	BEEPER_ON_MODE    = (1 << 9),//蜂鸣器常开，寻机模式。
} flightModeFlags_e;
extern uint32_t flightModeFlags;

#define DISABLE_FLIGHT_MODE(mask) disableFlightMode(mask)
#define ENABLE_FLIGHT_MODE(mask) enableFlightMode(mask)
#define FLIGHT_MODE(mask) (flightModeFlags & (mask))


//运行状态标志位
typedef enum 
{
	ACCELEROMETER_CALIBRATED  = (1 << 1),
	COMPASS_CALIBRATED        = (1 << 2),
	CALIBRATE_MAG             = (1 << 3),
	SMALL_ANGLE               = (1 << 4),
	FLASH_WRITING             = (1 << 5),
} stateFlags_t;
extern uint32_t stateFlags;

#define DISABLE_STATE(mask) (stateFlags &= ~(mask))
#define ENABLE_STATE(mask) (stateFlags |= (mask))
#define STATE(mask) (stateFlags & (mask))


uint32_t enableFlightMode(flightModeFlags_e mask);
uint32_t disableFlightMode(flightModeFlags_e mask);

void mwDisarm(void);
void mwArm(void);
void updateArmingStatus(void);

#endif

