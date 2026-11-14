#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <stdint.h>
#include <stddef.h>

#define WINDOW_SIZE 5u

typedef struct
{
    uint16_t data[WINDOW_SIZE]; // [0, 1, 2, 3, 4]
    size_t head;
    size_t count;
    uint32_t sum;
} MovingAverage;

void MovingAverage_Init(MovingAverage *filter);

void MovingAverage_Add(MovingAverage *filter, uint16_t value);

double MovingAverage_Get(const MovingAverage *filter);

#endif