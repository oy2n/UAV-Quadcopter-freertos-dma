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
    bool rcLinkState;				//遥控连接状态（true连接 false断开）
	bool failsafeActive;			//失控保护是否激活
	uint32_t rcLinkRealTime;		//遥控连接实时时间
	uint32_t throttleLowPeriod;		//遥控需要低油门时间（用于判断飞机是否着陆状态）
} failsafeState_t;



void rxInit(void);
void ppmTask(void *param);
bool rxLinkStatus(void);
void rxTask(void *param);

#endif
