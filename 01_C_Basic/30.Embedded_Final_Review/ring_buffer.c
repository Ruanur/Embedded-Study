#include "ring_buffer.h"

void RingBuffer_Init(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

int RingBuffer_Enqueue(RingBuffer *rb, uint8_t value)
{
    if (rb->count == RX_BUFFER_SIZE)
    {
        return 0;
    }

    rb->data[rb->head] = value;
    rb->head = (rb->head + 1) % RX_BUFFER_SIZE;
    rb->count++;

    return 1;
}

int RingBuffer_Dequeue(RingBuffer *rb, uint8_t *value)
{
    if (rb->count == 0)
    {
        return 0;
    }

    *value = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % RX_BUFFER_SIZE;
    rb->count--;

    return 1;
}
