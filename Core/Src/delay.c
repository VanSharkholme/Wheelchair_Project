#include "delay.h"

// void  delay_us(uint32_t nus)
// {
//     portENABLE_INTERRUPTS();
//      uint32_t cnt=0;
// 	__HAL_TIM_ENABLE(&htim6);
//     __HAL_TIM_SetCounter(&htim6,0);
// 	while( cnt < nus){
        
//        cnt=__HAL_TIM_GetCounter(&htim6);
       
//     }
// 	__HAL_TIM_DISABLE(&htim6);
// }

// void delay_ms(uint32_t ms){
//     portENABLE_INTERRUPTS();
//     __HAL_TIM_ENABLE(&htim6);
//     // delay_us(ms * 1000);
//     HAL_Delay(ms);
//    __HAL_TIM_DISABLE(&htim6);
    
// }

void delay_init(void)
{
#if 0
    REG_DEMCR     |= (u32)(1u << 24);   /* 使能DWT外设 */
    REG_DWT_CYCCNTR &= (u32)0u;         /* 清空计数值 */
    REG_DWT_CTRLR |= (u32)(1u <<  0);   /* 启动DWT计数 */
#else
    CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0UL;
#endif
}

void delay_us(uint32_t in_xus)
{
    uint32_t init_tick = REG_DWT_CYCCNTR;
    uint32_t num_tick = (SystemCoreClock / 1000000) *in_xus;
    while((REG_DWT_CYCCNTR - init_tick) < num_tick);
}

void delay_ms(uint32_t in_xms)
{
    for(uint32_t i = 0; i < in_xms; i++)
    {
        delay_us(1000);
    }
}
