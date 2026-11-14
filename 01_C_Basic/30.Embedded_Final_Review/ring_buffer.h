#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stddef.h>

#define RX_BUFFER_SIZE 32u

typedef struct
{
    uint8_t data[RX_BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t count;
} RingBuffer;

// 함수 선언
void RingBuffer_Init(RingBuffer *rb);

int RingBuffer_Enqueue(RingBuffer *rb, uint8_t value);

int RingBuffer_Dequeue(RingBuffer *rb, uint8_t *value);

#endif
