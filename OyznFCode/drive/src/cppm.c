#include "cppm.h"
#include "commander.h"
/* FreeRtos includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define CPPM_TIMER                   TIM9
#define CPPM_TIMER_RCC               RCC_APB2Periph_TIM9
#define CPPM_GPIO_RCC                RCC_AHB1Periph_GPIOA
#define CPPM_GPIO_PORT               GPIOA
#define CPPM_GPIO_PIN                GPIO_Pin_3
#define CPPM_GPIO_SOURCE             GPIO_PinSource3
#define CPPM_GPIO_AF                 GPIO_AF_TIM9

#define CPPM_TIM_PRESCALER           (168-1) 	//1us Tick

xQueueHandle captureQueue;
bool isAvailible;
uint16_t capureVal;
uint16_t capureValDiff;

void cppmInit(void)
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef  TIM_ICInitStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	RCC_AHB1PeriphClockCmd(CPPM_GPIO_RCC, ENABLE);
//	RCC_APB2PeriphClockCmd(CPPM_TIMER_RCC, ENABLE);
//
//	//≈‰÷√PPM–≈∫≈ ‰»Î“˝Ω≈£®PA3£©
//	GPIO_StructInit(&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Pin = CPPM_GPIO_PIN;
//	GPIO_Init(CPPM_GPIO_PORT, &GPIO_InitStructure);
//
//	GPIO_PinAFConfig(CPPM_GPIO_PORT, CPPM_GPIO_SOURCE, CPPM_GPIO_AF);
//
//	//≈‰÷√∂® ±∆˜1us tick
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Prescaler = CPPM_TIM_PRESCALER;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(CPPM_TIMER, &TIM_TimeBaseStructure);
//
//	//≈‰÷√ ‰»Î≤∂ªÒ
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICInit(CPPM_TIMER, &TIM_ICInitStructure);
//
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
	captureQueue = xQueueCreate(64, sizeof(uint16_t));
//
//	TIM_ITConfig(CPPM_TIMER, TIM_IT_Update | TIM_IT_CC2, ENABLE);
//	TIM_Cmd(CPPM_TIMER, ENABLE);
}

bool cppmIsAvailible(void)
{
	return isAvailible;
}

int cppmGetTimestamp(uint16_t *timestamp)
{
	ASSERT(timestamp);

	return xQueueReceive(captureQueue, timestamp, 20);
}

void cppmClearQueue(void)
{
	xQueueReset(captureQueue);
}


