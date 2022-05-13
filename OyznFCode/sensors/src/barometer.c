#include <math.h>
#include "barometer.h"
#include "bmp280.h"
#include "maths.h"
#include "nvic.h"

static u32 baroCalibrationTimeout = 0;
static bool baroCalibrationFinished = false;
float baroAltitude = 0;
static float baroGroundAltitude = 0;
static float baroGroundPressure = 101325.0f; // 101325 pascal, 1 standard atmosphere

bool baroInit(void)
{
	return bmp280Init();
}

bool baroIsCalibrationComplete(void)
{
    return baroCalibrationFinished;
}

void baroStartCalibration(void)
{
	baroCalibrationTimeout = getSysTickCnt();
	baroCalibrationFinished = false;
}

//气压值转换为海拔
static float pressureToAltitude(const float pressure)
{
    return (1.0f - powf(pressure / 101325.0f, 0.190295f)) * 4433000.0f;
}

//气压计1个标准大气压校准
static void performBaroCalibrationCycle(float baroPressureSamp)
{
	//慢慢收敛校准
    const float baroGroundPressureError = baroPressureSamp - baroGroundPressure;
    baroGroundPressure += baroGroundPressureError * 0.15f;

    if (ABS(baroGroundPressureError) < (baroGroundPressure * 0.00005f))  // 0.005% calibration error (should give c. 10cm calibration error)
	{   
        if ((getSysTickCnt() - baroCalibrationTimeout) > 250) 
		{
            baroGroundAltitude = pressureToAltitude(baroGroundPressure);
            baroCalibrationFinished = true;
        }
    }
    else 
	{
        baroCalibrationTimeout = getSysTickCnt();
    }
}

#define PRESSURE_SAMPLES_MEDIAN 3

/*
altitude pressure
      0m   101325Pa
    100m   100129Pa delta = 1196
   1000m    89875Pa
   1100m    88790Pa delta = 1085
At sea level an altitude change of 100m results in a pressure change of 1196Pa, at 1000m pressure change is 1085Pa
So set glitch threshold at 1000 - this represents an altitude change of approximately 100m.
*/
#define PRESSURE_DELTA_GLITCH_THRESHOLD 1000

static int32_t applyBarometerMedianFilter(int32_t newPressureReading)
{
    static int32_t barometerFilterSamples[PRESSURE_SAMPLES_MEDIAN];
    static int currentFilterSampleIndex = 0;
    static bool medianFilterReady = false;

    int nextSampleIndex = currentFilterSampleIndex + 1;
    if (nextSampleIndex == PRESSURE_SAMPLES_MEDIAN) 
	{
        nextSampleIndex = 0;
        medianFilterReady = true;
    }
    int previousSampleIndex = currentFilterSampleIndex - 1;
    if (previousSampleIndex < 0) 
	{
        previousSampleIndex = PRESSURE_SAMPLES_MEDIAN - 1;
    }
    const int previousPressureReading = barometerFilterSamples[previousSampleIndex];

    if (medianFilterReady) 
	{
        if (ABS(previousPressureReading - newPressureReading) < PRESSURE_DELTA_GLITCH_THRESHOLD) 
		{
            barometerFilterSamples[currentFilterSampleIndex] = newPressureReading;
            currentFilterSampleIndex = nextSampleIndex;
            return quickMedianFilter3(barometerFilterSamples);
        } 
		else
		{
            // glitch threshold exceeded, so just return previous reading and don't add the glitched reading to the filter array
            return barometerFilterSamples[previousSampleIndex];
        }
    } 
	else 
	{
        barometerFilterSamples[currentFilterSampleIndex] = newPressureReading;
        currentFilterSampleIndex = nextSampleIndex;
        return newPressureReading;
    }
}


void baroUpdate(baro_t *baro)
{
	//bmp280GetData(&baroPressure, &baroTemperature);
	bmp280GetDat();
	//中位值滤波
	baroPressure = applyBarometerMedianFilter(baroPressure * 10) / 10.0f;

	baro->pressure = baroPressure;
	baro->temperature = baroTemperature;
	if (!baroIsCalibrationComplete())
	{
		performBaroCalibrationCycle(baroPressure);
		baro->asl = 0.0f;
	}
	else
	{
		//计算去除地面高度后相对高度
        baro->asl = pressureToAltitude(baroPressure) - baroGroundAltitude;
	}

	baroAltitude = baro->asl;
}

