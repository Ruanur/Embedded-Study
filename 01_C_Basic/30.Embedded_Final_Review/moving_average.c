#include "moving_average.h"

void MovingAverage_Init(MovingAverage *filter)
{
    if (filter == NULL)
    {
        return;
    }
    
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
