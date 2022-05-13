/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sys.h"
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
static u32 sysTickCnt=0;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define CPPM_TIMER                   TIM9
extern TIM_HandleTypeDef htim9;
extern bool isAvailible;
extern uint16_t capureVal;
extern uint16_t capureValDiff;
extern xQueueHandle captureQueue;

static uint16_t prevCapureVal;
static bool captureFlag;

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/********************************************************
*getSysTickCnt()
*调度开启之前 返回 sysTickCnt
*调度开启之前 返回 xTaskGetTickCount()
*********************************************************/
u32 getSysTickCnt(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)	/*系统已经运行*/
		return xTaskGetTickCount();
	else
		return sysTickCnt;
}

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;
extern DMA_HandleTypeDef hdma_spi3_rx;
extern DMA_HandleTypeDef hdma_spi3_tx;
extern DMA_HandleTypeDef hdma_tim2_ch1;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim1;

/* USER CODE BEGIN EV */
volatile uint8_t FatFsCnt = 0;
volatile uint16_t Timer1, Timer2;

void SDTimer_Handler(void)
{
  if(Timer1 > 0)
    Timer1--;

  if(Timer2 > 0)
    Timer2--;
}
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
//	//http://www.st.com/mcu/forums-cat-6778-23.html
//	//****************************************************
//	//To test this application, you can use this snippet anywhere:
//	// //Let's crash the MCU!
//	// asm (" MOVS r0, #1 \n"
//	// " LDM r0,{r1-r2} \n"
//	// " BX LR; \n");
//	  PRESERVE8
//	  IMPORT printHardFault
//	  TST r14, #4
//	  ITE EQ
//	  MRSEQ R0, MSP
//	  MRSNE R0, PSP
//	  B printHardFault
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
//	motorsSetRatio(MOTOR_M1, 0);
//	motorsSetRatio(MOTOR_M2, 0);
//	motorsSetRatio(MOTOR_M3, 0);
//	motorsSetRatio(MOTOR_M4, 0);
//
//	DISABLE_ARMING_FLAG(ARMED);
//	LED0_OFF;
//
//	storeAssertSnapshotData(__FILE__, __LINE__);
//	while (1)
//	{}
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
//	motorsSetRatio(MOTOR_M1, 0);
//	motorsSetRatio(MOTOR_M2, 0);
//	motorsSetRatio(MOTOR_M3, 0);
//	motorsSetRatio(MOTOR_M4, 0);
//
//	DISABLE_ARMING_FLAG(ARMED);
//	LED0_OFF;
//
//	storeAssertSnapshotData(__FILE__, __LINE__);
//	while (1)
//	{}
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
//	motorsSetRatio(MOTOR_M1, 0);
//	motorsSetRatio(MOTOR_M2, 0);
//	motorsSetRatio(MOTOR_M3, 0);
//	motorsSetRatio(MOTOR_M4, 0);
//
//	DISABLE_ARMING_FLAG(ARMED);
//	LED0_OFF;
//
//	storeAssertSnapshotData(__FILE__, __LINE__);
//	while (1)
//	{}
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream0_IRQn 0 */

  /* USER CODE END DMA1_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_i2c1_rx);
  /* USER CODE BEGIN DMA1_Stream0_IRQn 1 */
  DMA1_Stream0Callback();
  /* USER CODE END DMA1_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi3_rx);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim2_ch1);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */
  DMA1_Stream5Callback();
  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_i2c1_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */
  DMA1_Stream6Callback();
  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break interrupt and TIM9 global interrupt.
  */
void TIM1_BRK_TIM9_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 0 */
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(__HAL_TIM_GET_FLAG(&htim9, TIM_IT_CC2) != RESET)
	{
		if(__HAL_TIM_GET_FLAG(&htim9, TIM_FLAG_CC2OF) != RESET)
		{
		  //TODO: Handle overflow error
		}

		capureVal = HAL_TIM_ReadCapturedValue(&htim9, TIM_CHANNEL_2);
		capureValDiff = capureVal - prevCapureVal;
		prevCapureVal = capureVal;

		xQueueSendFromISR(captureQueue, &capureValDiff, &xHigherPriorityTaskWoken);

		captureFlag = true;
		__HAL_TIM_CLEAR_FLAG(&htim9, TIM_IT_CC2);
	}

	if(__HAL_TIM_GET_FLAG(&htim9, TIM_IT_UPDATE) != RESET)
	{
		// Update input status
		isAvailible = (captureFlag == true);
		captureFlag = false;
		__HAL_TIM_CLEAR_FLAG(&htim9, TIM_IT_UPDATE);
	}
  /* USER CODE END TIM1_BRK_TIM9_IRQn 0 */
  HAL_TIM_IRQHandler(&htim9);
  /* USER CODE BEGIN TIM1_BRK_TIM9_IRQn 1 */

  /* USER CODE END TIM1_BRK_TIM9_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream7 global interrupt.
  */
void DMA1_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream7_IRQn 0 */

  /* USER CODE END DMA1_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi3_tx);
  /* USER CODE BEGIN DMA1_Stream7_IRQn 1 */

  /* USER CODE END DMA1_Stream7_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi1_rx);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */
  DMA2_Stream0Callback();
  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream4 global interrupt.
  */
void DMA2_Stream4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream4_IRQn 0 */

  /* USER CODE END DMA2_Stream4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream4_IRQn 1 */

  /* USER CODE END DMA2_Stream4_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream5 global interrupt.
  */
void DMA2_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream5_IRQn 0 */

  /* USER CODE END DMA2_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_spi1_tx);
  /* USER CODE BEGIN DMA2_Stream5_IRQn 1 */
  DMA2_Stream5Callback();
  /* USER CODE END DMA2_Stream5_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void  printHardFault(u32* hardfaultArgs)
{
//	motorsSetRatio(MOTOR_M1, 0);
//	motorsSetRatio(MOTOR_M2, 0);
//	motorsSetRatio(MOTOR_M3, 0);
//	motorsSetRatio(MOTOR_M4, 0);
//
//	DISABLE_ARMING_FLAG(ARMED);
//	LED0_OFF;
//
//	unsigned int stacked_r0;
//	unsigned int stacked_r1;
//	unsigned int stacked_r2;
//	unsigned int stacked_r3;
//	unsigned int stacked_r12;
//	unsigned int stacked_lr;
//	unsigned int stacked_pc;
//	unsigned int stacked_psr;
//
//	stacked_r0 = ((unsigned long) hardfaultArgs[0]);
//	stacked_r1 = ((unsigned long) hardfaultArgs[1]);
//	stacked_r2 = ((unsigned long) hardfaultArgs[2]);
//	stacked_r3 = ((unsigned long) hardfaultArgs[3]);
//
//	stacked_r12 = ((unsigned long) hardfaultArgs[4]);
//	stacked_lr = ((unsigned long) hardfaultArgs[5]);
//	stacked_pc = ((unsigned long) hardfaultArgs[6]);
//	stacked_psr = ((unsigned long) hardfaultArgs[7]);
//
//	printf("[Hard fault handler]\n");
//	printf("R0 = %x\n", stacked_r0);
//	printf("R1 = %x\n", stacked_r1);
//	printf("R2 = %x\n", stacked_r2);
//	printf("R3 = %x\n", stacked_r3);
//	printf("R12 = %x\n", stacked_r12);
//	printf("LR = %x\n", stacked_lr);
//	printf("PC = %x\n", stacked_pc);
//	printf("PSR = %x\n", stacked_psr);
//	printf("BFAR = %x\n", (*((volatile unsigned int *)(0xE000ED38))));
//	printf("CFSR = %x\n", (*((volatile unsigned int *)(0xE000ED28))));
//	printf("HFSR = %x\n", (*((volatile unsigned int *)(0xE000ED2C))));
//	printf("DFSR = %x\n", (*((volatile unsigned int *)(0xE000ED30))));
//	printf("AFSR = %x\n", (*((volatile unsigned int *)(0xE000ED3C))));
//
//	storeAssertSnapshotData(__FILE__, __LINE__);
//	while (1)
//	{}
}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
