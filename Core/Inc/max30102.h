#ifndef _GT911_H_
#define _GT911_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "gpio.h"
#include "main.h"
#include "arm_math.h"
#include "CT_IIC.h"
#include "usart.h"

#define MAX_INT_STATUS_1 0x00
#define MAX_INT_STATUS_2 0x01
#define MAX_INT_EN_1     0x02
#define MAX_INT_EN_2     0x03
#define MAX_FIFO_WR_PTR  0x04
#define MAX_OVERFLOW_CNT 0x05
#define MAX_FIFO_RD_PTR  0x06
#define MAX_DATA_REG     0x07
#define MAX_FIFO_CFG     0x08
#define MAX_MODE_CFG     0x09
#define MAX_SPO2_CFG     0x0A
#define MAX_LED1_PA      0x0C
#define MAX_LED2_PA      0x0D
#define MAX_MulLED_CFG1  0x11
#define MAX_MUlLED_CFG2  0x12
#define MAX_TEMP_INT     0x1F
#define MAX_TEMP_FRA     0x20
#define MAX_TEMP_CFG     0x21
#define MAX_REV_ID       0xFE
#define MAX_PART_ID      0xFF

void MAX_Init(void);
void MAX_INT_Init(void);
void MAX_Read_One_Sample(uint32_t* IR_buffer, uint32_t* RED_buffer);
void MAX_Read_N_Samples(uint8_t N, uint32_t* IR_buffer, uint32_t* RED_buffer);

#ifdef __cplusplus
}
#endif
#endif
