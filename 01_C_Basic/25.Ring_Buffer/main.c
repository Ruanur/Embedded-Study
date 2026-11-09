#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define BUFFER_SIZE 5u

typedef struct
{
    uint8_t data[BUFFER_SIZE]; // 데이터 저장 배열
    size_t head; // 다음 데이터를 기록할 위치
    size_t tail; // 다음 데이터를 읽어올 위치
    size_t count; // 현재 저장된 데이터 개수
} RingBuffer;

void RingBuffer_Init(RingBuffer *rb)
{
    // TODO 1: head = 0
    rb->head = 0;
    // TODO 2: tail = 0
    rb->tail = 0;
    // TODO 3: count = 0
    rb->count = 0;
}

int RingBuffer_Enqueue(RingBuffer *rb, uint8_t value)
{
    // TODO 1: 버퍼가 가득 찼는지 검사
    if (rb->count < BUFFER_SIZE)
    {
        // TODO 2: data[head]에 value 저장
        rb->data[rb->head] = value;

        // TODO 3: head를 다음 위치로 이동
        rb->head = (rb->head + 1) % BUFFER_SIZE;

        // TODO 4: count 증가
        rb->count++;

        // TODO 5: 성공하면 1, 실패하면 0 반환
        return 1;
    }
    else
    {
        return 0;
    }
}

int RingBuffer_Dequeue(RingBuffer *rb, uint8_t *value)
{
    // TODO 1: 버퍼가 비어 있는지 검사
    if (rb->count > 0)
    {
        // TODO 2: data[tail]의 값을 *value에 저장
        *value = rb->data[rb->tail];
        // TODO 3: tail을 다음 위치로 이동
        rb->tail = (rb->tail + 1) % BUFFER_SIZE;
        // TODO 4: count 감소
        rb->count--;
        // TODO 5: 성공하면 1, 실패하면 0 반환
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    RingBuffer rb;
    uint8_t value = 0;

    RingBuffer_Init(&rb);

    // 1. 데이터 10, 20, 30 저장
    RingBuffer_Enqueue(&rb, 10);
    printf("[Enqueue]\n");
    printf("Stored: %u\n", (unsigned)rb.data[0]);
    RingBuffer_Enqueue(&rb, 20);
    printf("Stored: %u\n", (unsigned)rb.data[1]);
    RingBuffer_Enqueue(&rb, 30);
    printf("Stored: %u\n", (unsigned)rb.data[2]);
    printf("\n");

    // 2. 데이터 2개 읽기
    printf("[Dequeue]\n");
    for (int i = 0; i < 2; i++)
    {
        if (RingBuffer_Dequeue(&rb, &value))
        {
            printf("Read: %u\n", (unsigned)value);
        }
    }
    printf("\n");


    // 3. 데이터 40, 50, 60, 70 저장
    printf("[Enqueue]\n");
    RingBuffer_Enqueue(&rb, 40);
    printf("Stored: %u\n", (unsigned)rb.data[3]);
    RingBuffer_Enqueue(&rb, 50);
    printf("Stored: %u\n", (unsigned)rb.data[4]);
    RingBuffer_Enqueue(&rb, 60);
    printf("Stored: %u\n", (unsigned)rb.data[0]);
    RingBuffer_Enqueue(&rb, 70);
    printf("Stored: %u\n", (unsigned)rb.data[1]);
    printf("\n");

    // 4. 버퍼가 가득 찬 상태에서 추가 저장 시도 - S
    printf("[Overflow Test]\n");
    if (!RingBuffer_Enqueue(&rb, 80))
    {
        printf("Buffer Full! Cannot store 80.\n");
    }
    printf("\n");

    // 5. 남은 데이터를 모두 읽기 - S
    printf("[Read All]\n");
    while (RingBuffer_Dequeue(&rb, &value))
    {
        /* code */
        printf("Read: %u\n", (unsigned)value);
    }
    printf("\n");

    // 6. 버퍼가 비었을 때 읽기 시도 - S
    printf("[Underflow Test]\n");
    if (RingBuffer_Dequeue(&rb, &value))
    {
        printf("Read: %u\n", (unsigned)value);
    }
    else
    {
        printf("Buffer Empty!\n");
    }

    return 0;
}