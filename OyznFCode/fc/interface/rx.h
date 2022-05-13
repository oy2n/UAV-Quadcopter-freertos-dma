#ifndef __RX_H
#define __RX_H
#include "sys.h"

enum 
{
	ROLL = 0,
	PITCH,
	THROTTLE,
	YAW,
	AUX1,
	AUX2,
	AUX3,
	AUX4,
	AUX5,
	AUX6,
	AUX7,
	AUX8,
	CH_NUM
};

extern uint16_t rcData[CH_NUM];

typedef struct 
{
	uint32_t realLinkTime;
	bool linkState;
	bool invalidPulse;
} rcLinkState_t;

typedef struct 
{
    bool rcLinkState;				//ң������״̬��true���� false�Ͽ���
	bool failsafeActive;			//ʧ�ر����Ƿ񼤻�
	uint32_t rcLinkRealTime;		//ң������ʵʱʱ��
	uint32_t throttleLowPeriod;		//ң����Ҫ������ʱ�䣨�����жϷɻ��Ƿ���½״̬��
} failsafeState_t;



void rxInit(void);
void ppmTask(void *param);
bool rxLinkStatus(void);
void rxTask(void *param);

#endif