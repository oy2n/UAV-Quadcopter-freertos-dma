#include "sys.h"
#include "usart.h"	
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"      //FreeRTOS 使用
#endif

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x) 
{ 
	x = x; 
} 
extern int consolePutchar(int ch);
//重定义fputc函数
int fputc(int ch, FILE *f)
{ 	
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
//	USART1->DR = (u8) ch;   
	consolePutchar(ch);	/*打印到上位机*/
	return ch;
}
#endif
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记

//初始化IO 串口1
//bound:波特率

#endif	

 



