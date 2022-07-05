#ifndef __IMU_H
#define __IMU_H

#include "sys.h"
#include "axis.h"
#include "maths.h"
#include "stabilizer_types.h"

extern float imuAttitudeYaw;


void imuInit(void);
void imuTransformVectorBodyToEarth(Axis3f * v);
void imuTransformVectorEarthToBody(Axis3f * v);
void imuUpdateAttitude(const sensorData_t *sensorData, state_t *state, float dt);

#endif


