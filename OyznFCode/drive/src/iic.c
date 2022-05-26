/*
 * iic.c
 *
 *  Created on: 2022��4��14��
 *      Author: oyzn
 */
#include "main.h"
#include "cmsis_os.h"

static xSemaphoreHandle iictxComplete;
static xSemaphoreHandle iicrxComplete;
//static xSemaphoreHandle isIICBusFreeMutex;
static xSemaphoreHandle isIICSendFreeMutex;
static xSemaphoreHandle isIICReadFreeMutex;

extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;
extern I2C_HandleTypeDef hi2c1;

void DMA1_Stream0Callback()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(__HAL_DMA_GET_TC_FLAG_INDEX(&hdma_i2c1_rx))
	{
		__HAL_DMA_CLEAR_FLAG(&hdma_i2c1_rx,DMA_FLAG_TCIF0_4);
		xSemaphoreGiveFromISR(iicrxComplete, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

void DMA1_Stream6Callback()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(__HAL_DMA_GET_TC_FLAG_INDEX(&hdma_i2c1_tx))
	{
		__HAL_DMA_CLEAR_FLAG(&hdma_i2c1_tx,DMA_FLAG_TCIF0_4);
		xSemaphoreGiveFromISR(iictxComplete, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

//bool IICWriteRead(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint16_t MemAddress,uint16_t MemAddSize,uint8_t *pData,uint16_t Size,uint8_t writeread)
//{
//    bool ack = true;
//    static bool isInit = false;
//
//	if (!isInit)
//	{
//		iictxComplete = xSemaphoreCreateBinary();
//		iicrxComplete = xSemaphoreCreateBinary();
//		isIICBusFreeMutex = xSemaphoreCreateMutex();
//		isInit = true;
//	}
//
//	xSemaphoreTake(isIICBusFreeMutex, portMAX_DELAY);
//	if(writeread)
//	{
//		ack = HAL_I2C_Mem_Write_DMA(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size);
//		if(!ack)
//			xSemaphoreTake(iictxComplete, portMAX_DELAY);
//	}
//	else
//	{
//		ack = HAL_I2C_Mem_Read_DMA(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size);
//		if(!ack)
//			xSemaphoreTake(iicrxComplete, portMAX_DELAY);
//	}
//	xSemaphoreGive(isIICBusFreeMutex);
//
//	return ack;
//}

void IICInit(void)
{
	iictxComplete = xSemaphoreCreateBinary();
	iicrxComplete = xSemaphoreCreateBinary();
	isIICSendFreeMutex = xSemaphoreCreateMutex();
	isIICReadFreeMutex = xSemaphoreCreateMutex();
}

bool IICWriteRegister(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint16_t MemAddress,uint16_t MemAddSize,uint8_t *pData,uint16_t Size)
{
	bool result = true;
	xSemaphoreTake(isIICSendFreeMutex, 0);
	if(HAL_DMA_GetState(&hdma_i2c1_tx) == HAL_DMA_STATE_READY)
	{
		if(HAL_I2C_GetState(hi2c) == HAL_I2C_STATE_READY)
		{
			//result = HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size,1000);
			result = HAL_I2C_Mem_Write_DMA(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size);
			if(!xSemaphoreTake(iictxComplete, 20))
			{
			      HAL_I2C_DeInit(hi2c);
			      HAL_I2C_Init(hi2c);
			}
		}
	}
	xSemaphoreGive(isIICSendFreeMutex);
	return result;
}

bool IICReadRegister(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint16_t MemAddress,uint16_t MemAddSize,uint8_t *pData,uint16_t Size)
{
	bool result = true;
	xSemaphoreTake(isIICReadFreeMutex, 0);
	if(HAL_DMA_GetState(&hdma_i2c1_rx) == HAL_DMA_STATE_READY)
	{
		if(HAL_I2C_GetState(hi2c) == HAL_I2C_STATE_READY)
		{
			//result = HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size,1000);
			result = HAL_I2C_Mem_Read_DMA(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size);
			if(!xSemaphoreTake(iicrxComplete, 20))
			{
			      HAL_I2C_DeInit(hi2c);
			      HAL_I2C_Init(hi2c);
			}
		}
	}
	xSemaphoreGive(isIICReadFreeMutex);
	return result;
}


