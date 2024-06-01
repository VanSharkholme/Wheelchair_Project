#ifndef DELAY_H
#define DELAY_H

#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include "FreeRTOS.h"

#define REG_DWT_CTRLR               (*(volatile uint32_t *)0xE0001000)
#define REG_DWT_CYCCNTR             (*(volatile uint32_t *)0xE0001004)
#define REG_DEMCR                   (*(volatile uint32_t *)0xE000EDFC)

extern TIM_HandleTypeDef htim6;
void delay_init(void);
void  delay_us(uint32_t nus);
void delay_ms(uint32_t ms);
#endif // !DELAY_H
