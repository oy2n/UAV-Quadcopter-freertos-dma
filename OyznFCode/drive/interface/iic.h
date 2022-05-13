/*
 * iic.h
 *
 *  Created on: 2022Äê4ÔÂ14ÈÕ
 *      Author: oyzn
 */

#ifndef INTERFACE_IIC_H_
#define INTERFACE_IIC_H_

#define wirteiic 1
#define readiic  0

//extern HAL_StatusTypeDef IICWriteRead(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint16_t MemAddress,uint16_t MemAddSize,uint8_t *pData,uint16_t Size,uint8_t writeread);
bool IICWriteRegister(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint16_t MemAddress,uint16_t MemAddSize,uint8_t *pData,uint16_t Size);
bool IICReadRegister(I2C_HandleTypeDef *hi2c,uint16_t DevAddress,uint16_t MemAddress,uint16_t MemAddSize,uint8_t *pData,uint16_t Size);
void IICInit(void);
extern I2C_HandleTypeDef hi2c1;

#endif /* INTERFACE_IIC_H_ */
