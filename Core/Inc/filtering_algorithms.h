//
// Created by 13651 on 2024/6/6.
//

#ifndef WHEELCHAIR_PROJECT_FILTERING_ALGORITHMS_H
#define WHEELCHAIR_PROJECT_FILTERING_ALGORITHMS_H
#include "main.h"
#include "stdlib.h"

#define BUFFER_LEN 50

typedef struct {
    float64_t data_buffer[BUFFER_LEN];
    uint8_t index;
    float64_t avg;
    float64_t MinValue;
    float64_t MaxValue;
    float64_t RemovedValue;
} StructBuffer;

//typedef struct {
//    float64_t avg;
//} StructWindowAVG;
//
typedef struct {
    float64_t *MinDeque;
    float64_t *MaxDeque;
    uint8_t headMax, tailMax, cntMax;
    uint8_t headMin, tailMin, cntMin;
} StructWindowMinMax;

//StructWindowAVG* slide_avg_init(uint8_t window_len, StructBuffer *data_buffer);
float64_t update_window_avg(StructBuffer *buffer, float64_t new_value);
StructWindowMinMax *slide_minmax_init();
void update_window_MinMax(StructWindowMinMax *handle,
                          float64_t new_value, float64_t removing_value,
                          float64_t *retMax, float64_t *retMin);
#endif //WHEELCHAIR_PROJECT_FILTERING_ALGORITHMS_H
