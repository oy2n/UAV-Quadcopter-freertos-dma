#ifndef __POWER_CONTROL_H
#define __POWER_CONTROL_H
#include "sys.h"
#include "stabilizer_types.h"

typedef struct 
{
	u16 m1; //Öµ·¶Î§£º0-1000
	u16 m2;
	u16 m3;
	u16 m4;
	
}motorPWM_t;

extern motorPWM_t motorPWM;

void powerControlInit(void);
bool powerControlTest(void);
void powerControl(control_t *control);

void getMotorPWM(motorPWM_t* get);
void setMotorPWM(bool enable, u32 m1_set, u32 m2_set, u32 m3_set, u32 m4_set);
#endif 
