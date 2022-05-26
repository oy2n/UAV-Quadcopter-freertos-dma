#include "mpu6000.h"
#include "spi1.h"
#include "delay.h"
#include "cmsis_os.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;

// Bits
#define BIT_SLEEP                   0x40
#define BIT_H_RESET                 0x80
#define BITS_CLKSEL                 0x07
#define MPU_CLK_SEL_PLLGYROX        0x01
#define MPU_CLK_SEL_PLLGYROZ        0x03
#define MPU_EXT_SYNC_GYROX          0x02
#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18
#define BITS_FS_2G                  0x00
#define BITS_FS_4G                  0x08
#define BITS_FS_8G                  0x10
#define BITS_FS_16G                 0x18
#define BITS_FS_MASK                0x18
#define BITS_DLPF_CFG_256HZ         0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07
#define BIT_INT_ANYRD_2CLEAR        0x10
#define BIT_RAW_RDY_EN              0x01
#define BIT_I2C_IF_DIS              0x10
#define BIT_INT_STATUS_DATA         0x01
#define BIT_GYRO                    3
#define BIT_ACC                     2
#define BIT_TEMP                    1


#define ACC_GYRO_RAWDATA_LEN	14

#define DISABLE_MPU6000()	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
#define ENABLE_MPU6000()   	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);

static bool isInit = false;

const uint8_t READWRITE_CMD = 0x80;

static xSemaphoreHandle spitxComplete;
static xSemaphoreHandle spirxComplete;
static xSemaphoreHandle isSPISendFreeMutex;
static xSemaphoreHandle isSPIReadFreeMutex;

void spiSetSpeed(uint16_t speed);

u8 Gyrobuffer[6];
u8 Accbuffer[6];

bool mpu6000SpiWriteRegister(uint8_t reg, uint8_t data)
{
	bool result = true;

	xSemaphoreTake(isSPISendFreeMutex, 0);

    ENABLE_MPU6000();
    result = result && !HAL_SPI_Transmit_DMA(&hspi1, &reg, sizeof(reg));
    xSemaphoreTake(spitxComplete, portMAX_DELAY);
    result = result && !HAL_SPI_Transmit_DMA(&hspi1, &data, sizeof(data));
    xSemaphoreTake(spitxComplete, portMAX_DELAY);
    DISABLE_MPU6000();
	xSemaphoreGive(isSPISendFreeMutex);
	return result;
}
//mpu6000SpiReadRegister(MPU_RA_WHO_AM_I, 1, &id);
bool mpu6000SpiReadRegister(uint8_t reg, uint16_t length, uint8_t *data)
{
	bool result = true;
	xSemaphoreTake(isSPIReadFreeMutex, 0);

	ENABLE_MPU6000();
	if(HAL_DMA_GetState(&hdma_spi1_tx) == HAL_DMA_STATE_READY)
	{
		if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
		{
			reg |= READWRITE_CMD;
	//		result = result && !HAL_SPI_Transmit(&hspi1,&reg,1,1000);
			result = result && !HAL_SPI_Transmit_DMA(&hspi1,&reg,1);
			if(!xSemaphoreTake(spitxComplete, 20))
			{
				HAL_SPI_DeInit(&hspi1);
				HAL_SPI_Init(&hspi1);
			}
		}
		//等待传输完成
	}

	if(HAL_DMA_GetState(&hdma_spi1_rx) == HAL_DMA_STATE_READY)
	{
		if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
		{
			//result = result && !HAL_SPI_Receive(&hspi1,data,length,1000);
			result = result && !HAL_SPI_Receive_DMA(&hspi1,data,length);
			if(!xSemaphoreTake(spirxComplete,20))
			{
				HAL_SPI_DeInit(&hspi1);
				HAL_SPI_Init(&hspi1);
			}
		}
	}

	DISABLE_MPU6000();
	xSemaphoreGive(isSPIReadFreeMutex);
	return result;
}

bool mpu6000Init(void)
{
	if (isInit) return true;
	spitxComplete = xSemaphoreCreateBinary();
	spirxComplete = xSemaphoreCreateBinary();
	isSPISendFreeMutex = xSemaphoreCreateMutex();
	isSPIReadFreeMutex = xSemaphoreCreateMutex();
	//复位MPU6000
	mpu6000SpiWriteRegister(MPU_RA_PWR_MGMT_1, BIT_H_RESET);
	HAL_Delay(50);
	mpu6000SpiWriteRegister(MPU_RA_SIGNAL_PATH_RESET, BIT_GYRO | BIT_ACC | BIT_TEMP);
	HAL_Delay(50);
	mpu6000SpiWriteRegister(MPU_RA_PWR_MGMT_1, BIT_H_RESET);//复位两次增加传感器稳定性
	HAL_Delay(50);
	mpu6000SpiWriteRegister(MPU_RA_SIGNAL_PATH_RESET, BIT_GYRO | BIT_ACC | BIT_TEMP);
	HAL_Delay(50);
	
	//读取ID
	u8 id = 0x00;
	mpu6000SpiReadRegister(MPU_RA_WHO_AM_I, 1, &id);
	spiSetSpeed(SPI_BAUDRATEPRESCALER_128);
	//读取正常，初始化
	if(id == MPU6000_WHO_AM_I_CONST)
	{
		//设置X轴陀螺作为时钟
		mpu6000SpiWriteRegister(MPU_RA_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROX);
		HAL_Delay(15);
		
		//禁止I2C接口
		mpu6000SpiWriteRegister(MPU_RA_USER_CTRL, BIT_I2C_IF_DIS);
		HAL_Delay(15);
		mpu6000SpiWriteRegister(MPU_RA_PWR_MGMT_2, 0x00);
		HAL_Delay(15);
		
		// Accel Sample Rate 1kHz
		// Gyroscope Output Rate =  1kHz when the DLPF is enabled
		mpu6000SpiWriteRegister(MPU_RA_SMPLRT_DIV, 0);//设置采样率
		HAL_Delay(15);
		
		//设置陀螺仪 +/- 2000 DPS量程
		mpu6000SpiWriteRegister(MPU_RA_GYRO_CONFIG, FSR_2000DPS << 3);
		HAL_Delay(15);
		
		//设置加速度 +/- 8 G 量程
		mpu6000SpiWriteRegister(MPU_RA_ACCEL_CONFIG, FSR_8G << 3);
		HAL_Delay(15);
		
		//设置中断引脚功能
		mpu6000SpiWriteRegister(MPU_RA_INT_PIN_CFG, 0 << 7 | 0 << 6 | 0 << 5 | 1 << 4 | 0 << 3 | 0 << 2 | 0 << 1 | 0 << 0);//中断引脚配置
		HAL_Delay(15);
		
		//设置低通滤波带宽
		mpu6000SpiWriteRegister(MPU_RA_CONFIG, BITS_DLPF_CFG_98HZ);
		HAL_Delay(1);
		
		//printf("MPU6000 SPI connection [OK].\n");
		isInit = true;
	}
	else
	{
		//printf("MPU6000 SPI connection [FAIL].\n");
	}
	spiSetSpeed(SPI_BAUDRATEPRESCALER_8);
	return isInit;
}

bool mpu6000GyroRead(Axis3i16* gyroRaw)
{
	if(!isInit) 
		return false;
	//u8 buffer[6];
	mpu6000SpiReadRegister(MPU_RA_GYRO_XOUT_H, 6, &Gyrobuffer[0]);
	gyroRaw->x = (((int16_t) Gyrobuffer[0]) << 8) | Gyrobuffer[1];
	gyroRaw->y = (((int16_t) Gyrobuffer[2]) << 8) | Gyrobuffer[3];
	gyroRaw->z = (((int16_t) Gyrobuffer[4]) << 8) | Gyrobuffer[5];
	return true;
}

bool mpu6000AccRead(Axis3i16* accRaw)
{
	if(!isInit) 
		return false;
	//u8 buffer[6];
	mpu6000SpiReadRegister(MPU_RA_ACCEL_XOUT_H, 6, &Accbuffer[0]);
	accRaw->x = (((int16_t) Accbuffer[0]) << 8) | Accbuffer[1];
	accRaw->y = (((int16_t) Accbuffer[2]) << 8) | Accbuffer[3];
	accRaw->z = (((int16_t) Accbuffer[4]) << 8) | Accbuffer[5];
	return true;
}

void spiSetSpeed(uint16_t speed)
{
  hspi1.Instance = SPI1;
  hspi1.Init.BaudRatePrescaler = speed;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
	Error_Handler();
  }
}

void DMA2_Stream0Callback()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(__HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_rx))
	{
		//释放传输完成信号量
		xSemaphoreGiveFromISR(spirxComplete, &xHigherPriorityTaskWoken);
		if (xHigherPriorityTaskWoken)
		{
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		__HAL_DMA_CLEAR_FLAG(&hdma_spi1_rx,DMA_FLAG_TCIF2_6); //清除全部中断标志
	}
}

void DMA2_Stream5Callback()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(__HAL_DMA_GET_TC_FLAG_INDEX(&hdma_spi1_tx))
	{
		//释放传输完成信号量
		xSemaphoreGiveFromISR(spitxComplete, &xHigherPriorityTaskWoken);
		if (xHigherPriorityTaskWoken)
		{
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		__HAL_DMA_CLEAR_FLAG(&hdma_spi1_tx,DMA_FLAG_TCIF2_6); //清除全部中断标志
	}
}

