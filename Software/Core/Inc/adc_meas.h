#ifndef ADC_MEAS_H
#define ADC_MEAS_H

#include "main.h"
extern ADC_HandleTypeDef hadc1;
#define adc_Offset 5
float ADC_Voltage(uint8_t Samples);

#endif
