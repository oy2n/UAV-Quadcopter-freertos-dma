#ifndef __SENSORS_H
#define __SENSORS_H
#include "stabilizer_types.h"
#include "config.h"

/*传感器读取更新频率*/
#define GYRO_UPDATE_RATE		RATE_500_HZ
#define ACC_UPDATE_RATE			RATE_500_HZ
#define MAG_UPDATE_RATE			RATE_10_HZ
#define BARO_UPDATE_RATE		RATE_50_HZ

extern sensorData_t sensors;

void sensorsTask(void *param);
void sensorsInit(void);			/*传感器初始化*/
bool sensorsTest(void);			/*传感器测试*/
bool sensorsAreCalibrated(void);	/*传感器数据校准*/
void sensorsAcquire(sensorData_t *sensors, const u32 tick);/*获取传感器数据*/
void getSensorRawData(Axis3i16* acc, Axis3i16* gyro, Axis3i16* mag);
bool sensorsIsMagPresent(void);

/* 单独测量传感器数据 */
bool sensorsReadGyro(Axis3f *gyro);
bool sensorsReadAcc(Axis3f *acc);
bool sensorsReadMag(Axis3f *mag);
bool sensorsReadBaro(baro_t *baro);

#endif //__SENSORS_H
