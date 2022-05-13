#include "system.h"

/*底层硬件初始化*/
void systemInit(void)
{
	IICInit();
	ledInit();			/*led初始化*/
	ledStripInit();		/*初始化WS2812RGB灯*/
	beeperInit();		/*蜂鸣器初始化*/
	configParamInit();	/*初始化配置参数*/
	pmInit();			/*电源电压管理初始化*/
	rxInit();			/*遥控器ppm信号接收初始化*/
	usblinkInit();		/*USB通信初始化*/
	atkpInit();			/*传输协议初始化*/
	consoleInit();		/*打印初始化*/
	stabilizerInit();	/*电机 PID 姿态解算初始化*/
}
