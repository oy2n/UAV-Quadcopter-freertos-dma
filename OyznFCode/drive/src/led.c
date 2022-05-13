#include "led.h"
#include "delay.h"
#include "nvic.h"

static uint32_t warningLedTimer = 0;

typedef enum
{
    WARNING_LED_OFF = 0,
    WARNING_LED_ON,
    WARNING_LED_FLASH
} warningLedState_e;

static warningLedState_e warningLedState = WARNING_LED_OFF;

void ledInit(void)
{
;
}

void warningLedON(void)
{
    warningLedState = WARNING_LED_ON;
}

void warningLedOFF(void)
{
    warningLedState = WARNING_LED_OFF;
}

void warningLedFlash(void)
{
    warningLedState = WARNING_LED_FLASH;
}

void warningLedRefresh(void)
{
    switch (warningLedState) 
	{
        case WARNING_LED_OFF:
            LED0_OFF;
            break;
        case WARNING_LED_ON:
            LED0_ON;
            break;
        case WARNING_LED_FLASH:
            LED0_TOGGLE;
            break;
    }
}

void warningLedUpdate(void)
{
	if (getSysTickCnt() - warningLedTimer > 500)//500ms刷新一次灯的状态
	{
		warningLedRefresh();
		warningLedTimer = getSysTickCnt();
	}
}

