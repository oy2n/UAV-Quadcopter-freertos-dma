#ifndef __STATE_CONTROL_H
#define __STATE_CONTROL_H
#include "stabilizer_types.h"

enum pidIndex
{
	RATE_ROLL = 0,
	RATE_PITCH,
	RATE_YAW,
	ANGLE_ROLL,
	ANGLE_PITCH,
	ANGLE_YAW,
	VELOCITY_Z,
	POSHOLD_Z,
	VELOCITY_XY,
	POSHOLD_XY,	
	PID_NUM
};

void stateControlInit(void);
bool stateControlTest(void);
void stateControl(const sensorData_t *sensorData, const state_t *state, setpoint_t *setpoint, control_t *control, const u32 tick);
void stateControlResetYawHolding(void);
void stateControlSetVelocityZPIDIntegration(float integ);
#endif /*__STATE_CONTROL_H */

