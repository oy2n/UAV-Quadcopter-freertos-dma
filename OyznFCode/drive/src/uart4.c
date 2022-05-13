
#include <uart4.h>
#include "stdio.h"
//DMA_InitTypeDef DMA_InitStructure;
uint16_t DMA1_MEM_LEN;//保存DMA每次数据传送的长度
/*
DMA1的各通道配置这里的传输形式是固定的,这点要根据不同的情况来修改
从存储器->外设模式/8位数据宽度/存储器增量模式
DMA_CHx:DMA通道CHx      cpar:外设地址
cmar:存储器地址         cndtr:数据传输量
*/
//void Quad_DMA_Config(DMA_Channel_TypeDef* DMA_CHx,uint32_t cpar,uint32_t cmar,uint16_t cndtr)
//{
////  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
////  DMA_DeInit(DMA_CHx);   											        //将DMA的通道1寄存器重设为缺省值
////  DMA1_MEM_LEN=cndtr;
////  DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
////  DMA_InitStructure.DMA_MemoryBaseAddr =cmar;				//DMA内存基地址
////  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
////  DMA_InitStructure.DMA_BufferSize = cndtr;  												//DMA通道的DMA缓存的大小
////  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
////  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  					//内存地址寄存器递增
////  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//数据宽度为8位
////  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        //数据宽度为8位
////  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  									       //工作在正常缓存模式
////  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                  //DMA通道 x拥有中优先级
////  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                           //DMA通道x没有设置为内存到内存传输
////  DMA_Init(DMA_CHx, &DMA_InitStructure);//根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
//}


void DMA_Send_Vcan(float userdata1,float userdata2,
									 float userdata3,float userdata4,
									 float userdata5,float userdata6,
									 float userdata7,float userdata8)
{
	static uint8_t databuf[36];
	uint8_t _cnt=0;
	databuf[_cnt++]=0x03;
	databuf[_cnt++]=0xfc;
	Float2Byte(&userdata1,databuf,_cnt);//3
	_cnt+=4;
	Float2Byte(&userdata2,databuf,_cnt);//7
	_cnt+=4;
	Float2Byte(&userdata3,databuf,_cnt);//11
	_cnt+=4;
	Float2Byte(&userdata4,databuf,_cnt);//15
	_cnt+=4;
	Float2Byte(&userdata5,databuf,_cnt);//19
	_cnt+=4;
	Float2Byte(&userdata6,databuf,_cnt);//23
	_cnt+=4;
	Float2Byte(&userdata7,databuf,_cnt);//27
	_cnt+=4;
	Float2Byte(&userdata8,databuf,_cnt);//31
	_cnt+=4;
	databuf[_cnt++]=0xfc;//35
	databuf[_cnt++]=0x03;//36
	//USART1_Send_Dma(databuf,_cnt);
	Serial_Data_Send(databuf,_cnt);
}


void UART2_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);//这里跟分析fputc时是一样的
  USART_SendData(USART2 , tx_buf);//发送字符数组里的单个字符
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
}

void USART2_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART2, USART_FLAG_TC);
  USART_ClearITPendingBit(USART2, USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART2, *tx_buf);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART2, USART_FLAG_TC);
    USART_ClearITPendingBit(USART2, USART_FLAG_TXE);
    tx_buf++;
  }
}


unsigned char Buffer[2]={9,8};
void USART2_Init(unsigned long bound)
{
//  GPIO_InitTypeDef GPIO_InitStructure;
//  USART_InitTypeDef USART_InitStructure;
//
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO
//                         |RCC_APB2Periph_GPIOA , ENABLE);//串口2
//
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//串口2 低速
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//
//  USART_InitStructure.USART_BaudRate = bound;//
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8bits
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;//stop bit is 1
//  USART_InitStructure.USART_Parity = USART_Parity_No;//no parity
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
//  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//enable tx and rx
//  USART_Init(USART2, &USART_InitStructure);//
//
//  USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//rx interrupt is enable
//  USART_Cmd(USART2, ENABLE);
  
  //USART2_Send((unsigned char *)Buffer,2);
  //UART2_Send(0xAA);
}

//u16 GPS_ISR_CNT=0;
//uint16 Ublox_Try_Cnt=0;
//uint16 Ublox_Try_Makesure=0;
//uint16 Ublox_Try_Start=0;
//uint8 Ublox_Data[95]={0};
//uint16 Ublox_Cnt=0;
//uint16 GPS_Update_finished=0;
//uint16 GPS_Update_finished_Correct_Flag=0;
//Testime GPS_Time_Delta;
//void USART2_IRQHandler(void)//解析GPS输出的UBLOX  PVT协议
//{
//  unsigned char ch;
//  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
//  {
//    //Test_Period(&GPS_Time_Delta1);
//    if(GPS_ISR_CNT<=2000)
//    {
//      GPS_ISR_CNT++;
//    }
//
//    ch=USART_ReceiveData(USART2);
//
//    if(Ublox_Try_Makesure==1)
//    {
//      Ublox_Data[Ublox_Cnt++]=ch;
//      if(Ublox_Cnt==94)
//      {
//        Ublox_Cnt=0;
//        Ublox_Try_Makesure=0;
//        GPS_Update_finished=1;
//        GPS_Update_finished_Correct_Flag=1;
//        Test_Period(&GPS_Time_Delta);//GPS数据更新间隔测试
//      }
//    }
//
//    if(Ublox_Try_Makesure==0
//       &&ch==0xB5)//出现帧头首字节，判断帧头是否完整
//    {
//      Ublox_Try_Start=1;
//      Ublox_Try_Cnt=0;
//    }
//
//    if(Ublox_Try_Start==1)
//    {
//      Ublox_Try_Cnt++;
//      if(Ublox_Try_Cnt>=5)
//      {
//        Ublox_Try_Start=0;
//        Ublox_Try_Cnt=0;
//
//        if(ch==0x5C) Ublox_Try_Makesure=1;//确认为帧头，开始接受
//        else Ublox_Try_Makesure=0;//非帧头，复位等待再次确认
//      }
//    }
//  }
//  USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//
//}


