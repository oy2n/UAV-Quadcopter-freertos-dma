#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 

void busIIC_Init(void);
bool i2cWrite(uint8_t addr, uint8_t reg, uint8_t data);
bool i2cRead(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
bool i2cWriteBuffer(uint8_t addr, uint8_t reg, uint8_t len, const uint8_t * data);


#endif




