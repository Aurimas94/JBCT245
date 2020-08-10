#ifndef MAX31855_H
#define MAX31855_H

#include <string.h>
#include "main.h"

//Defines

#define CS_1_LOW HAL_GPIO_WritePin(CS_1_GPIO_Port,CS_1_Pin,GPIO_PIN_RESET);
#define CS_1_HIGH HAL_GPIO_WritePin(CS_1_GPIO_Port,CS_1_Pin,GPIO_PIN_SET);

typedef struct {
	uint8_t internal_temp;
	uint8_t ext_temp;
	uint8_t error_state;
} MAX31855_byte_struct;

int32_t MAX31855_Read_Internal_Temp(void);
int32_t MAX31855_Read_Probe_Temp(void);
uint8_t MAX31855_Read_Status(void);
#endif
