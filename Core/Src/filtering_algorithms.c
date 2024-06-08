//
// Created by 13651 on 2024/6/6.
//
#include "filtering_algorithms.h"


//StructWindowAVG *slide_avg_init(uint8_t window_len, StructBuffer *data_buffer) {
//    StructWindowAVG *ret = (StructWindowAVG *) malloc(sizeof(StructWindowAVG));
//    ret->window_len = window_len;
//    ret->window = data_buffer;
//    memset(ret->window, 0, sizeof(float64_t) * window_len);
//    ret->index = 0;
//    ret->avg = 0;
//    return ret;
//}

StructWindowMinMax *slide_minmax_init()
{
    StructWindowMinMax *ret = (StructWindowMinMax *) malloc(sizeof(StructWindowMinMax));
    ret->MaxDeque = (float64_t *) malloc(sizeof(float64_t) * BUFFER_LEN);
    ret->MinDeque = (float64_t *) malloc(sizeof(float64_t) * BUFFER_LEN);
    ret->headMax = 0;
    ret->headMin = 0;
    ret->tailMax = 0;
    ret->tailMin = 0;
    ret->cntMax = 0;
    ret->cntMin = 0;
    return ret;
}

float64_t update_window_avg(StructBuffer *buffer, float64_t new_value) {
    if (buffer->index == BUFFER_LEN - 1)
        HAL_UART_Transmit(&huart1, (uint8_t *) "\n", 1, 1000);
    buffer->avg -= buffer->data_buffer[buffer->index] / BUFFER_LEN;
    buffer->RemovedValue = buffer->data_buffer[buffer->index];
    buffer->data_buffer[buffer->index] = new_value;
    buffer->avg += new_value / BUFFER_LEN;
    buffer->index = (buffer->index + 1) % BUFFER_LEN;
    return buffer->avg;
}

void update_window_MinMax(StructWindowMinMax *handle,
                          float64_t new_value, float64_t RemovedValue,
                          float64_t *retMax, float64_t *retMin)
{
    uint8_t k = BUFFER_LEN;
    if(handle->MaxDeque[handle->headMax] == RemovedValue)
    {
        handle->headMax = (handle->headMax + 1) % k;
        handle->cntMax--;
    }
    if(handle->MinDeque[handle->headMin] == RemovedValue)
    {
        handle->headMin = (handle->headMin + 1) % k;
        handle->cntMin--;
    }
    while(handle->cntMax > 0 && handle->MaxDeque[((handle->tailMax - 1) % k + k) % k] < new_value)
    {
        handle->tailMax = ((handle->tailMax - 1) % k + k) % k;
        handle->cntMax--;
    }
    while(handle->cntMin > 0 && handle->MinDeque[((handle->tailMin - 1) % k + k) % k] > new_value)
    {
        handle->tailMin = ((handle->tailMin - 1) % k + k) % k;
        handle->cntMin--;
    }
    handle->MaxDeque[handle->tailMax] = new_value;
    handle->tailMax = (handle->tailMax + 1) % k;
    handle->cntMax++;
    *retMax = handle->MaxDeque[handle->headMax];
    handle->MinDeque[handle->tailMin] = new_value;
    handle->tailMin = (handle->tailMin + 1) % k;
    handle->cntMin++;
    *retMin = handle->MinDeque[handle->headMin];
//    printf("%d\n", max);
}
