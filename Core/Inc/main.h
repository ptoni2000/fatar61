/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOA
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOA
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define PR1_Pin GPIO_PIN_0
#define PR1_GPIO_Port GPIOB
#define PR2_Pin GPIO_PIN_1
#define PR2_GPIO_Port GPIOB
#define PR3_Pin GPIO_PIN_2
#define PR3_GPIO_Port GPIOB
#define RI3_Pin GPIO_PIN_10
#define RI3_GPIO_Port GPIOB
#define RI4_Pin GPIO_PIN_11
#define RI4_GPIO_Port GPIOB
#define RI5_Pin GPIO_PIN_12
#define RI5_GPIO_Port GPIOB
#define RI6_Pin GPIO_PIN_13
#define RI6_GPIO_Port GPIOB
#define RI7_Pin GPIO_PIN_14
#define RI7_GPIO_Port GPIOB
#define RI8_Pin GPIO_PIN_15
#define RI8_GPIO_Port GPIOB
#define PR4_Pin GPIO_PIN_3
#define PR4_GPIO_Port GPIOB
#define PR5_Pin GPIO_PIN_4
#define PR5_GPIO_Port GPIOB
#define PR6_Pin GPIO_PIN_5
#define PR6_GPIO_Port GPIOB
#define PR7_Pin GPIO_PIN_6
#define PR7_GPIO_Port GPIOB
#define PR8_Pin GPIO_PIN_7
#define PR8_GPIO_Port GPIOB
#define RI1_Pin GPIO_PIN_8
#define RI1_GPIO_Port GPIOB
#define RI2_Pin GPIO_PIN_9
#define RI2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
