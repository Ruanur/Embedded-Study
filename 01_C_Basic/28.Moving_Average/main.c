#include <stdio.h>
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

void MovingAverage_Init(MovingAverage *filter)
{
    // TODO: head, count, sum을 0으로 초기화
    filter->head = 0;
    filter->count = 0;
    filter->sum = 0;
}

void MovingAverage_Add(MovingAverage *filter, uint16_t value)
{
    if (filter->count < WINDOW_SIZE)
    {
        // TODO 1: 새로운 값을 sum에 더하기
        filter->sum += value;
        // TODO 2: count 증가
        filter->count++;
    }
    else
    {
        // TODO 3: 오래된 값을 sum에서 빼기
        // 0(old) -> 1 -> 2 -> 3 -> 4 -> 0(new)
        filter->sum -= filter->data[filter->head];
        // TODO 4: 새로운 값을 sum에 더하기
        filter->sum += value;
    }

    // TODO 5: data[head]에 value 저장
    filter->data[filter->head] = value;

    // TODO 6: head 순환 이동
    filter->head = (filter->head + 1) % WINDOW_SIZE;
}

double MovingAverage_Get(const MovingAverage *filter)
{
    // TODO 1: count가 0이라면 0.0 반환
    if (filter->count == 0)
    {
        return 0.0;
    }
    // TODO 2: 평균 계산 및 반환
    return (double)filter->sum / filter->count;
}

int main(void)
{
    MovingAverage filter;
    MovingAverage_Init(&filter);

    uint16_t samples[] =
        {
            20, 22, 21, 80, 23, 24, 25};

    size_t sampleCount =
        sizeof(samples) / sizeof(samples[0]);

    printf("[Moving Average Filter]\n");

    for (size_t i = 0; i < sampleCount; i++)
    {
        MovingAverage_Add(&filter, samples[i]);

        printf(
            "Input: %u | Average: %.2f | Count: %zu\n",
            (unsigned)samples[i],
            MovingAverage_Get(&filter),
            filter.count);
    }
    /*
    [Moving Average Filter]
    Input: 20 | Average: 20.00 | Count: 1
    Input: 22 | Average: 21.00 | Count: 2
    Input: 21 | Average: 21.00 | Count: 3
    Input: 80 | Average: 35.75 | Count: 4
    Input: 23 | Average: 33.20 | Count: 5
    Input: 24 | Average: 34.00 | Count: 5
    Input: 25 | Average: 34.60 | Count: 5
    */
    return 0;
}
