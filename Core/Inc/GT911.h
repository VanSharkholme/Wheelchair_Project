#ifndef _GT911_H_
#define _GT911_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "gpio.h"
#include "delay.h"
#include "main.h"
#include "usart.h"


#define Init_RST_CLK() __HAL_RCC_GPIOI_CLK_ENABLE()
#define Init_INT_CLK() __HAL_RCC_GPIOH_CLK_ENABLE()
#define Init_SYSCFG_CLK() __HAL_RCC_SYSCFG_CLK_ENABLE() 

#define GT_RES_Clr() HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_RESET)
#define GT_RES_Set() HAL_GPIO_WritePin(CTP_RST_GPIO_Port, CTP_RST_Pin, GPIO_PIN_SET)

#define GT_INT_Clr() HAL_GPIO_WritePin(CTP_INT_GPIO_Port, CTP_INT_Pin, GPIO_PIN_RESET)
#define GT_INT_Set() HAL_GPIO_WritePin(CTP_INT_GPIO_Port, CTP_INT_Pin, GPIO_PIN_SET)

#define GT_ReadINT   HAL_GPIO_ReadPin(CTP_INT_GPIO_Port, CTP_INT_Pin)


#define GT_Write_ADDR 0xBA
#define GT_Read_ADDR  0xBB
#define GT_ID_ADDR    0x8140
#define GT_CFG_START  0x8047
#define GT_Point_ADDR 0x814E
#define GT_COORD_ADDR 0x8150

// 0x804D初始值0000 1101

extern uint32_t GT911_CFG_TBL[186];
extern uint32_t coord_buf[4];
void GT_GPIOInit(void);
int8_t GT_WR_DATA(uint32_t addr,uint32_t* data, uint32_t len);
int8_t GT_RD_DATA(uint32_t addr,uint32_t len,uint32_t *value);
void GT_Init(uint8_t wr_cfg);
void NVIC_Configuration(void);
void EXTI_GT_INTInit(void);
void GT_IRQHandler(void);
void GT911_READ_CFG(uint8_t show);
#ifdef __cplusplus
}
#endif
#endif
