
#ifndef __USART_H
#define __USART_H

#include "sys.h"
#include "GPS.h"

void USART1_Init(unsigned long bound);
void USART1_Send(unsigned char *tx_buf, int len);
void USART1_Receive(unsigned char *rx_buf, int len);
void UART1_Send(unsigned char tx_buf);
void wust_sendware(unsigned char *wareaddr, int16_t waresize);
void Quad_DMA1_USART1_SEND(u32 SendBuff,u16 len);//DMA---USART1´«Êä
void DMA_Send_Vcan(float userdata1,float userdata2,
									 float userdata3,float userdata4,
									 float userdata5,float userdata6,
									 float userdata7,float userdata8);
void USART1_Send_Dma(uint8_t *dma_buf,uint16_t dma_cnt);


void USART2_Init(unsigned long bound);

void USART3_Init(unsigned long bound);
void USART3_Send(unsigned char tx_buf);
void UART3_Send(unsigned char *tx_buf, int len);
void USART2_Send(unsigned char *tx_buf, int len);


void USART4_Init(unsigned long bound);
void SBUS_USART5_Init(void);



extern uint8_t RecBag[3];
extern uint8_t US_100_Cnt;


extern unsigned int GPS_Data_Cnt;
extern u16 GPS_ISR_CNT;
extern  u8 GPS_Buf[2][100];
extern uint8_t Ublox_Data[95];

extern uint16_t GPS_Update_finished,GPS_Update_finished_Correct_Flag;
extern Testime GPS_Time_Delta;
//extern RingBuff_t SBUS_Ringbuf,OpticalFlow_Ringbuf;


#endif


