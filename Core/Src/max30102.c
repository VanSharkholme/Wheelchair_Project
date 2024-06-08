#include "max30102.h"

void MAX_IIC_Init(I2C_SW_Handle_t* handle)
{
    handle->scl_pin = PPG_SCL_Pin;
    handle->scl_port = PPG_SCL_GPIO_Port;
    handle->sda_pin = PPG_SDA_Pin;
    handle->sda_port = PPG_SDA_GPIO_Port;
    handle->slave_addr = 0x57;
    handle->slave_address_width = Slave_Address_7Bit;
    handle->slave_reg_addr_width = One_Byte;
    handle->slave_reg_value_width = One_Byte;
    handle->speed_mode = Fast_Mode;
}

int8_t MAX_WR_DATA(uint32_t addr, uint32_t* data, uint32_t len)
{
    return i2c_reg_write(&hi2c_max, addr, len, data);
    // return HAL_I2C_Mem_Write(&hi2c2, 0xAE, addr, 1, data, 1, 1000);
}

int8_t MAX_WR_ONE_DATA(uint32_t addr, uint32_t data)
{
    return i2c_reg_write(&hi2c_max, addr, 1, &data);
    // return HAL_I2C_Mem_Write(&hi2c2, 0xAE, addr, 1, &data, 1, 1000);
}

int8_t MAX_RD_DATA(uint32_t addr, uint32_t len, uint32_t *value)
{
    // return HAL_I2C_Mem_Read(&hi2c2, 0xAF, addr, 1, value, len, 1000);
    return i2c_reg_read(&hi2c_max, addr, len, value);
}

void MAX_Init(void)
{
    uint32_t buf[1] = {0};
    MAX_IIC_Init(&hi2c_max);
    // Reset MX30102
    MAX_WR_ONE_DATA(MAX_MODE_CFG, 0x40);
    MAX_RD_DATA(MAX_INT_STATUS_1, 1, buf);
    // MX30102 Param Init
    MAX_WR_ONE_DATA(MAX_INT_EN_1, 0xC0);    // almost full && data ready
    MAX_WR_ONE_DATA(MAX_FIFO_WR_PTR, 0x00);
    MAX_WR_ONE_DATA(MAX_OVERFLOW_CNT, 0x00);
    MAX_WR_ONE_DATA(MAX_FIFO_RD_PTR, 0x00);
    MAX_WR_ONE_DATA(MAX_FIFO_CFG, 0x4F);    // 4 sample average, no rollover, almost full at 17 samples
    MAX_WR_ONE_DATA(MAX_MODE_CFG, 0x03);    // Spo2 mode
    MAX_WR_ONE_DATA(MAX_SPO2_CFG, 0x27);    // adc full scale 4096nA, sample rate 100Hz, pulse width 411us(18bit adc)
    MAX_WR_ONE_DATA(MAX_LED1_PA, 0x24);
    MAX_WR_ONE_DATA(MAX_LED2_PA, 0x24);
    // Read Part ID
    buf[0] = 0;
    MAX_RD_DATA(MAX_PART_ID, 1, buf);
    char str[25] = "";
    sprintf(str, "MX30102 Part ID: %02x\n", buf[0]);
    HAL_UART_Transmit(&huart1, (uint8_t *)str, 25, 1000);
}

void MAX_INT_Init(void)
{
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void MAX_Read_One_Sample(uint32_t* IR_buffer, uint32_t* RED_buffer)
{
    uint32_t buffer_tmp[6] = {0};
    MAX_RD_DATA(MAX_DATA_REG, 6, buffer_tmp);
    *RED_buffer = (buffer_tmp[0] << 16) | (buffer_tmp[1] << 8) | buffer_tmp[2];
    *IR_buffer = (buffer_tmp[3] << 16) | (buffer_tmp[4] << 8) | buffer_tmp[5];
}

void MAX_Read_N_Samples(uint8_t N, uint32_t* IR_buffer, uint32_t* RED_buffer)
{
    uint32_t buffer_tmp[255 * 6] = {0};
    MAX_RD_DATA(MAX_DATA_REG, 6 * N, buffer_tmp);
    for(uint8_t i = 0; i < N; i++)
    {
        RED_buffer[i] = (buffer_tmp[6*i] << 16) | (buffer_tmp[6*i+1] << 8) | buffer_tmp[6*i+2];
        IR_buffer[i] = (buffer_tmp[6*i+3] << 16) | (buffer_tmp[6*i+4] << 8) | buffer_tmp[6*i+5];
    }
}
