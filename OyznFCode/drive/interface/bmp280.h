#ifndef __BMP280_H
#define __BMP280_H
#include "sys.h"

#define BMP280_I2C_ADDR					(0x76)
#define BMP280_DEFAULT_CHIP_ID			(0x58)

#define BMP280_CHIP_ID					(0xD0)  /* Chip ID Register */
#define BMP280_RST_REG					(0xE0)  /* Softreset Register */
#define BMP280_STAT_REG					(0xF3)  /* Status Register */
#define BMP280_CTRL_MEAS_REG			(0xF4)  /* Ctrl Measure Register */
#define BMP280_CONFIG_REG				(0xF5)  /* Configuration Register */
#define BMP280_PRESSURE_MSB_REG			(0xF7)  /* Pressure MSB Register */
#define BMP280_PRESSURE_LSB_REG			(0xF8)  /* Pressure LSB Register */
#define BMP280_PRESSURE_XLSB_REG		(0xF9)  /* Pressure XLSB Register */
#define BMP280_TEMPERATURE_MSB_REG		(0xFA)  /* Temperature MSB Reg */
#define BMP280_TEMPERATURE_LSB_REG		(0xFB)  /* Temperature LSB Reg */
#define BMP280_TEMPERATURE_XLSB_REG		(0xFC)  /* Temperature XLSB Reg */


#define BMP280_TEMPERATURE_CALIB_DIG_T1_LSB_REG             (0x88)
#define BMP280_PRESSURE_TEMPERATURE_CALIB_DATA_LENGTH       (24)

#define BMP280_OVERSAMP_SKIPPED         (0x00)
#define BMP280_OVERSAMP_1X              (0x01)
#define BMP280_OVERSAMP_2X              (0x02)
#define BMP280_OVERSAMP_4X              (0x03)
#define BMP280_OVERSAMP_8X              (0x04)
#define BMP280_OVERSAMP_16X             (0x05)

#define BMP280_FILTER_COEFF_OFF         (0x00)
#define BMP280_FILTER_COEFF_2           (0x01)
#define BMP280_FILTER_COEFF_4           (0x02)
#define BMP280_FILTER_COEFF_8           (0x03)
#define BMP280_FILTER_COEFF_16          (0x04)

#define BMP280_FORCED_MODE             	(0x01)
#define BMP280_NORMAL_MODE				(0x03)

extern float baroTemperature,baroPressure;
bool bmp280Init(void);
void bmp280GetPressure(void);
void bmp280GetDat();
void bmp280GetData(float* pressure, float* temperature);
u32 bmp280CompensateP(s32 adcP);
u32 bmp280CompensateT(s32 adcT);
bool bmp280SpiReadRegister(uint8_t reg, uint8_t length, uint8_t *data);
float bmp280PressureToAltitude(float* pressure/*, float* groundPressure, float* groundTemp*/);

#endif


