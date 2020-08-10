#include "adc_meas.h"
#include "main.h"

uint8_t indx = 0;
uint16_t newVal = 0;
uint16_t Sum = 0;
uint16_t readArray[Window_Size];
uint16_t average = 0;
float avg_Voltage = 0;
float avg_Current = 0;
float ADC_Voltage(uint8_t Samples) {

	uint16_t Sum = 0;
	uint8_t i;
	for (i = 0; i < Samples; i++) {
		HAL_ADC_Start(&hadc1);
		if (HAL_ADC_PollForConversion(&hadc1, 5) == HAL_OK) {
			Sum = Sum + HAL_ADC_GetValue(&hadc1);
		}
	}
	average = (Sum / Samples) - adc_Offset;
	return average;

}
