/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.23.2. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
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
#include "GT911.h"
#include "main.h"
#include "usart.h"
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
    GT_Init(0);
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
    uint32_t buf[4] = {0};
    uint32_t instruction[1] = {0};
    for(uint8_t i = 0; i < 4; i++)
        coord_buf[i] = 0;
    GT_RD_DATA(GT_Point_ADDR, 1, coord_buf);
    char str[18] = "";
    if (coord_buf[0] & 0x80)
    {
        coord_buf[0] = 0;
        GT_RD_DATA(GT_COORD_ADDR, 4, coord_buf);
        x = (int32_t) (coord_buf[0] | (coord_buf[1] << 8));
        y = (int32_t) (coord_buf[2] | (coord_buf[3] << 8));
        GT_WR_DATA(GT_Point_ADDR, instruction, 1);
        sprintf(str, "x=%d,y=%d,", y, x);
//        HAL_UART_Transmit(&huart1, (uint8_t *)str, 18, 1000);
        return true;
    } else
    {
        GT_WR_DATA(GT_Point_ADDR, instruction, 1);
        return false;
    }
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
