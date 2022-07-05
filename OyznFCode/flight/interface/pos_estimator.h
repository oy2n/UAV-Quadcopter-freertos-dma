#ifndef __POS_ESTIMATOR_H
#define __POS_ESTIMATOR_H
#include "stabilizer_types.h"

void updatePositionEstimator(const sensorData_t *sensorData, state_t *state, float dt);
bool posEstimatorIsCalibrationComplete(void);
void posEstimatorReset(void);


#endif
