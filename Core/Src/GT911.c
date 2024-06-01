#include "GT911.h"

uint32_t GT911_CFG_TBL[186] = {
    0x41,0x20,0x03,0xE0,0x01, 0x0A,0x0F,0x20,0x01,0x0A, // 0x8050
    0x28,0x0F,0x5A,0x3C,0x03, 0x05,0x00,0x00,0x00,0x00,	// 0x805A
    0x00,0x00,0x05,0x00,0x00, 0x00,0x00,0x8A,0x2A,0x0C, // 0x8064
    0x32,0x34,0x0C,0x08,0x00, 0x00,0x00,0x03,0x02,0x25, // 0x806E
    0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,	// 0x8078

    0x00,0x28,0x55,0x94,0xC5, 0x02,0x07,0x00,0x00,0x04,	// 0x8082
    0x8D,0x2B,0x00,0x80,0x32, 0x00,0x75,0x3A,0x00,0x6C,	// 0x808C
    0x43,0x00,0x64,0x4F,0x00, 0x64,0x00,0x00,0x00,0x00,	// 0x8096
    0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,	// 0x80A0
    0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,	// 0x80AA

    0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,	// 0x80B4
    0x00,0x00,0x18,0x16,0x14, 0x12,0x10,0x0E,0x0C,0x0A,	// 0x80BE
    0x08,0x06,0x04,0x02,0xFF, 0xFF,0x00,0x00,0x00,0x00,	// 0x80C8
    0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,	// 0x80D2
    0x00,0x00,0x24,0x22,0x21, 0x20,0x1F,0x1E,0x1D,0x1C,	// 0x80DC
    
    0x18,0x16,0x13,0x12,0x10, 0x0F,0x0A,0x08,0x06,0x04,	// 0x80E6
    0x02,0x00,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0x00,0x00,	// 0x80F0
    0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,	// 0x80FA
    0x00,0x00,0x00,0x00,0x58, 0x01
};

uint32_t coord_buf[4] = {0};

void GT_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    Init_RST_CLK();
	GPIO_InitStructure.Pin=CTP_RST_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(CTP_RST_GPIO_Port, &GPIO_InitStructure);

    Init_INT_CLK();
	GPIO_InitStructure.Pin=CTP_INT_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(CTP_INT_GPIO_Port, &GPIO_InitStructure);
}


//配置中断控制器NVIC
void NVIC_Configuration(void)
{
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

//配置GT_INT管脚为中断
void EXTI_GT_INTInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = CTP_INT_Pin;
  	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  	GPIO_InitStructure.Pull = GPIO_NOPULL;
  	HAL_GPIO_Init(CTP_INT_GPIO_Port, &GPIO_InitStructure);
}

void GT_IIC_Init(I2C_SW_Handle_t* handle)
{
    handle->scl_pin = CTP_SCL_Pin;
    handle->scl_port = CTP_SCL_GPIO_Port;
    handle->sda_pin = CTP_SDA_Pin;
    handle->sda_port = CTP_SDA_GPIO_Port;
    handle->slave_addr = 0x5D;
    handle->slave_address_width = Slave_Address_7Bit;
    handle->slave_reg_addr_width = Two_Byte;
    handle->slave_reg_value_width = One_Byte;
    handle->speed_mode = Fast_Mode;
}

int8_t GT_WR_DATA(uint32_t addr,uint32_t* data, uint32_t len)
{
	return i2c_reg_write(&hi2c, addr, len, data);
}

int8_t GT_RD_DATA(uint32_t addr,uint32_t len,uint32_t *value)
{
	return i2c_reg_read(&hi2c, addr, len, value);
}

void GT_Init(uint8_t wr_cfg)
{
	uint32_t touchIC_ID[4]={0};
	uint32_t instruction[2] = {0x00, 0x01};
	// IIC_GPIOInit();
    GT_IIC_Init(&hi2c);
	GT_GPIOInit();
	delay_ms(5);
	GT_RES_Clr();
	delay_ms(10); 
  GT_RES_Set();
	delay_ms(10);
	GT_RES_Clr();
	GT_INT_Clr();
	delay_ms(20);
	if(GT_Read_ADDR==0x28)
	{
		GT_INT_Set();
	}
	else
	{
		GT_INT_Clr();
	}
	delay_ms(20);
	GT_RES_Set();
	delay_ms(20);
	GT_INT_Set();
    delay_ms(10); //退出sleep mode
    EXTI_GT_INTInit();
	// 读取触摸芯片型号
	GT_RD_DATA(GT_ID_ADDR,4,touchIC_ID);
    char str[30] = "";
    sprintf(str, "Touch IC: GT%c%c%c%c\n", touchIC_ID[0], touchIC_ID[1], touchIC_ID[2], touchIC_ID[3]);
    HAL_UART_Transmit(&huart1, (uint8_t *)str, 30, 1000);
	// GT911软复位
	instruction[0] = 0x02;
	GT_WR_DATA(0x8040, instruction, 1);
	delay_ms(100);
	if(wr_cfg){
		GT_WR_DATA(GT_CFG_START, GT911_CFG_TBL, 184);
		instruction[0] = 0x00;
		for(int i = 0; i < 184; i++){
			instruction[0] += GT911_CFG_TBL[i];
		}
		instruction[0] = ~((uint8_t)instruction[0]) + 1;
		GT_WR_DATA(0x80FF, instruction, 2);
		delay_ms(100);
	}
	instruction[0] = 0x00;
	GT_WR_DATA(0x8040, instruction, 1);
	delay_ms(100);
	GT911_READ_CFG(1);
	sprintf(str, "Touch Init Complete\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)str, 30, 1000);
}

void GT911_READ_CFG(uint8_t show)
{
	uint32_t buf[186] = {0};
	GT_RD_DATA(GT_CFG_START, 186, buf);
	char str[6] = "";
	uint8_t tmp = 0;
	for(int i = 0; i < 184; i++)
	{
		tmp += buf[i];
		sprintf(str, "%02x ", buf[i]);
		if(show)
			HAL_UART_Transmit(&huart1, (uint8_t *)str, 6, 1000);
	}
	tmp = ~((uint8_t)tmp) + 1;
	// sprintf(str, "%02x\n", tmp);
	// HAL_UART_Transmit(&huart1, (uint8_t *)str, 5, 1000);
	if(tmp == buf[184])
		HAL_UART_Transmit(&huart1, "CFG Checksum correct\n", 22, 1000);
}
