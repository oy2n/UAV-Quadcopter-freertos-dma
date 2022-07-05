#ifndef __BAROMETER_H
#define __BAROMETER_H

#include "sys.h"
#include "stabilizer_types.h"

extern float baroAltitude;

bool baroInit(void);
bool baroIsCalibrationComplete(void);
void baroStartCalibration(void);
void baroUpdate(baro_t *baro);

#endif

