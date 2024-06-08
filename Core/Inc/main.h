/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sdram.h"
#include "CT_IIC.h"
#include "stdio.h"
#include "max30102.h"
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PPG_SDA_Pin GPIO_PIN_3
#define PPG_SDA_GPIO_Port GPIOE
#define PPG_SCL_Pin GPIO_PIN_4
#define PPG_SCL_GPIO_Port GPIOE
#define PPG_INT_Pin GPIO_PIN_5
#define PPG_INT_GPIO_Port GPIOE
#define CTP_RST_Pin GPIO_PIN_8
#define CTP_RST_GPIO_Port GPIOI
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOB
#define CTP_SCL_Pin GPIO_PIN_6
#define CTP_SCL_GPIO_Port GPIOH
#define CTP_INT_Pin GPIO_PIN_7
#define CTP_INT_GPIO_Port GPIOH
#define CTP_SDA_Pin GPIO_PIN_3
#define CTP_SDA_GPIO_Port GPIOI
#define LCD_BL_Pin GPIO_PIN_5
#define LCD_BL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
