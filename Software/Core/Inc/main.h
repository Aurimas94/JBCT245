/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define btn_Dn_Pin GPIO_PIN_0
#define btn_Dn_GPIO_Port GPIOC
#define btn_Dn_EXTI_IRQn EXTI0_IRQn
#define btn_Up_Pin GPIO_PIN_1
#define btn_Up_GPIO_Port GPIOC
#define btn_Up_EXTI_IRQn EXTI1_IRQn
#define btn_OK_Pin GPIO_PIN_2
#define btn_OK_GPIO_Port GPIOC
#define btn_OK_EXTI_IRQn EXTI2_IRQn
#define btn_OnOff_Pin GPIO_PIN_3
#define btn_OnOff_GPIO_Port GPIOC
#define btn_OnOff_EXTI_IRQn EXTI3_IRQn
#define ENC_A_Pin GPIO_PIN_0
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_1
#define ENC_B_GPIO_Port GPIOA
#define Current_1_Pin GPIO_PIN_2
#define Current_1_GPIO_Port GPIOA
#define Current_2_Pin GPIO_PIN_3
#define Current_2_GPIO_Port GPIOA
#define TFT_CS_Pin GPIO_PIN_4
#define TFT_CS_GPIO_Port GPIOA
#define TFT_SCK_Pin GPIO_PIN_5
#define TFT_SCK_GPIO_Port GPIOA
#define TFT_RST_Pin GPIO_PIN_6
#define TFT_RST_GPIO_Port GPIOA
#define TFT_MOSI_Pin GPIO_PIN_7
#define TFT_MOSI_GPIO_Port GPIOA
#define TFT_BCLT_Pin GPIO_PIN_4
#define TFT_BCLT_GPIO_Port GPIOC
#define TFT_DC_Pin GPIO_PIN_5
#define TFT_DC_GPIO_Port GPIOC
#define HIB_Pin GPIO_PIN_10
#define HIB_GPIO_Port GPIOB
#define CS_2_Pin GPIO_PIN_12
#define CS_2_GPIO_Port GPIOB
#define SCK_2_Pin GPIO_PIN_13
#define SCK_2_GPIO_Port GPIOB
#define MISO_2_Pin GPIO_PIN_14
#define MISO_2_GPIO_Port GPIOB
#define ZC_1_Pin GPIO_PIN_6
#define ZC_1_GPIO_Port GPIOC
#define ZC_1_EXTI_IRQn EXTI9_5_IRQn
#define ZC_2_Pin GPIO_PIN_7
#define ZC_2_GPIO_Port GPIOC
#define ZC_2_EXTI_IRQn EXTI9_5_IRQn
#define btn_Rot_Pin GPIO_PIN_8
#define btn_Rot_GPIO_Port GPIOC
#define CS_1_Pin GPIO_PIN_15
#define CS_1_GPIO_Port GPIOA
#define SCK_1_Pin GPIO_PIN_10
#define SCK_1_GPIO_Port GPIOC
#define MISO_1_Pin GPIO_PIN_11
#define MISO_1_GPIO_Port GPIOC
#define Drive_1_Pin GPIO_PIN_8
#define Drive_1_GPIO_Port GPIOB
#define Drive_2_Pin GPIO_PIN_9
#define Drive_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
