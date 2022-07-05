#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

#include "sys.h"
#include "stabilizer_types.h"

#define GRAVITY_CMSS    980.665f
#define GRAVITY_MSS     9.80665f

#define CALIBRATING_ACC_CYCLES          400

			
extern Axis3i16 accADC;

bool accIsCalibrationComplete(void);
void accSetCalibrationCycles(uint16_t calibrationCyclesRequired);
bool accInit(float accUpdateRate);
void accUpdate(Axis3f *acc);

#endif

