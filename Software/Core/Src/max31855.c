#include "max31855.h"

extern SPI_HandleTypeDef hspi3;

int32_t MAX31855_Read_Internal_Temp(void) {
	uint8_t tmp0, tmp1, tmp2, tmp3, dataRx[4];
	int32_t dataBuf, dataBuf1;

	CS_1_LOW
	;
	HAL_SPI_Receive(&hspi3, (uint8_t*) dataRx, 4, 1000);
	if (__HAL_SPI_GET_FLAG(&hspi3, SPI_FLAG_RXNE) != 1) {
		CS_1_HIGH
		;
		tmp0 = dataRx[0];
		tmp1 = dataRx[1];
		tmp2 = dataRx[2];
		tmp3 = dataRx[3];
		dataBuf = tmp3 | tmp2 << 8 | tmp1 << 16 | tmp0 << 24;
		dataBuf1 = dataBuf & 0x0F; // check fault codes
		if (dataBuf1 != 0) {
			return 0;
		} else {
			dataBuf = (dataBuf & 0xFFFF) >> 4;    // remove probe & fault values
			if (dataBuf & 0x2000)
				dataBuf |= 0xFFFF000;  // 2s complement bits if negative
			dataBuf = dataBuf * (int32_t) 625 / (int32_t) 10;
			return dataBuf;
		}
	} else if (__HAL_SPI_GET_FLAG(&hspi3, HAL_SPI_ERROR_NONE) != 0) {
		return HAL_ERROR;
	}

}
int32_t MAX31855_Read_Probe_Temp(void) {
	uint8_t tmp0, tmp1, tmp2, tmp3, dataRx[4];
	int32_t dataBuf, dataBuf1;

	CS_1_LOW
	;
	HAL_SPI_Receive(&hspi3, (uint8_t*) dataRx, 4, 1000);
	if (__HAL_SPI_GET_FLAG(&hspi3, SPI_FLAG_RXNE) != 1) {
		CS_1_HIGH
		;
		tmp0 = dataRx[0];
		tmp1 = dataRx[1];
		tmp2 = dataRx[2];
		tmp3 = dataRx[3];
		dataBuf = tmp3 | tmp2 << 8 | tmp1 << 16 | tmp0 << 24;
		dataBuf1 = dataBuf & 0x0F; // check fault codes
		if (dataBuf1 != 0) {
			return 0;
		} else {
			dataBuf = dataBuf >> 18;       // remove unused ambient values
			if (dataBuf & 0x2000) {
				dataBuf |= 0xFFFE000;
			} // 2s complement bits if negative
			dataBuf *= (int32_t) 250;
			return dataBuf;
		}
	} else if (__HAL_SPI_GET_FLAG(&hspi3, HAL_SPI_ERROR_NONE) != 0) {
		return HAL_ERROR;
	}

}
uint8_t MAX31855_Read_Status(void) {
	uint8_t tmp0, tmp1, tmp2, tmp3, dataRx[4];
	int32_t dataBuf;

	CS_1_LOW
	;
	HAL_SPI_Receive(&hspi3, (uint8_t*) dataRx, 4, 1000);
	if (__HAL_SPI_GET_FLAG(&hspi3, SPI_FLAG_RXNE) != 1) {
		CS_1_HIGH
		;
		tmp0 = dataRx[0];
		tmp1 = dataRx[1];
		tmp2 = dataRx[2];
		tmp3 = dataRx[3];
		dataBuf = tmp3 | tmp2 << 8 | tmp1 << 16 | tmp0 << 24;

		if ((dataBuf & 0x01) != 0) {

			return 1;
		} else if ((dataBuf & 0x02) != 0) {

			return 2;
		} else if ((dataBuf & 0x04) != 0) {

			return 3;
		} else
			return 0;
	} else if (__HAL_SPI_GET_FLAG(&hspi3, HAL_SPI_ERROR_NONE) != 0) {
		return HAL_ERROR;
	}

}

