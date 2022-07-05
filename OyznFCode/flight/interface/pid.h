#ifndef __PID_H
#define __PID_H
#include "config_param.h"
#include "filter.h"

typedef struct
{
	float desired;		//< set point
	float error;        //< error
	float prevError;    //< previous error
	float integ;        //< integral
	float deriv;        //< derivative
	float kp;           //< proportional gain
	float ki;           //< integral gain
	float kd;           //< derivative gain
	float outP;         //< proportional output (debugging)
	float outI;         //< integral output (debugging)
	float outD;         //< derivative output (debugging)
	float iLimit;       //< integral limit
	float outputLimit;  //< total PID output limit, absolute value. '0' means no limit.
	float dt;           //< delta-time dt
	bool enableDFilter; //< filter for D term enable flag
	biquadFilter_t dFilter;  //< filter for D term
} PidObject;

/*pid结构体初始化*/
void pidInit(PidObject* pid, float kp, float ki, float kd, float iLimit, float outputLimit, float dt, bool enableDFilter, float cutoffFreq);
float pidUpdate(PidObject* pid, float error);
void pidReset(PidObject* pid);
void pidResetIntegral(PidObject* pid);
void pidSetIntegral(PidObject* pid, float integ);
#endif /* __PID_H */
