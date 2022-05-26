#include "compass_qmc5883l.h"
#include "main.h"
#include "iic.h"
uint8_t qmcbuf[6];

bool qmc5883lInit()
{
    bool ack = true;
    uint8_t trash = 0x01;
    uint8_t ini = QMC5883L_MODE_CONTINUOUS | QMC5883L_ODR_200HZ | QMC5883L_OSR_512 | QMC5883L_RNG_8G;
    ack = ack && !HAL_I2C_Mem_Write(&hi2c1, QMC5883L_MAG_I2C_ADDRESS, 0x0B, I2C_MEMADD_SIZE_8BIT, &trash, 1, TM_GLOB);
    ack = ack && !HAL_I2C_Mem_Write(&hi2c1, QMC5883L_MAG_I2C_ADDRESS, QMC5883L_REG_CONF1, I2C_MEMADD_SIZE_8BIT, &ini, 1, TM_GLOB);

    if (!ack) {
        return false;
    }

    return true;
}

bool qmc5883lRead(Axis3i16* magRaw)
{
    uint8_t ack = 0;

	if(!IICReadRegister(&hi2c1,QMC5883L_MAG_I2C_ADDRESS,QMC5883L_REG_DATA_OUTPUT_X,I2C_MEMADD_SIZE_8BIT,&qmcbuf[0],6))
	{
		magRaw->x = (int16_t)(qmcbuf[1] << 8 | qmcbuf[0]);
		magRaw->z = (int16_t)(qmcbuf[3] << 8 | qmcbuf[2]);
		magRaw->y = (int16_t)(qmcbuf[5] << 8 | qmcbuf[4]);
		ack = 1;
	}
	return ack;
}



