#ifndef __CONFIG_PARAM_H
#define __CONFIG_PARAM_H
#include "sys.h"
#include "stabilizer_types.h"
#include "state_control.h"

/*参数保存地址配置*/
#define CONFIG_PARAM_SIZE	(1020*1024)
#define CONFIG_PARAM_ADDR 	(FLASH_BASE + CONFIG_PARAM_SIZE)	


typedef struct 
{
	float kp;
	float ki;
	float kd;
} pidInit_t;

typedef struct
{
	int16_t accZero[3];
	int16_t accGain[3];
} accBias_t;

typedef struct
{
	int16_t magZero[3];
} magBias_t;

typedef struct 
{
    int16_t rollDeciDegrees;
    int16_t pitchDeciDegrees;
    int16_t yawDeciDegrees;
} boardAlignment_t;

typedef struct	
{
	u8 version;						/*软件版本号*/
	pidInit_t pid[PID_NUM];			/*PID参数*/
	accBias_t accBias;				/*加速度校准值*/
	magBias_t magBias;				/*磁力计校准值*/
	boardAlignment_t boardAlign;	/*板子微调*/
	u16 thrustBase;					/*油门基础值*/
	u8 cksum;						/*校验*/
} configParam_t;


extern configParam_t configParam;

void configParamInit(void);	/*参数配置初始化*/
void configParamTask(void* param);	/*参数配置任务*/
bool configParamTest(void);

void configParamGiveSemaphore(void);
void resetConfigParam(void);
void saveConfigAndNotify(void);

#endif /*__CONFIG_PARAM_H */

