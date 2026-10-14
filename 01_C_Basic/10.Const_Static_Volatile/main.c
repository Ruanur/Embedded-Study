#include <stdio.h>

// const: 수정하지 않을 데이터, 읽기 전용으로 다루어야 하는 값이나 데이터를 표현한다.
// static: 정적 저장 기간, 지역 변수에 사용하면 함수 호출이 끝나도 값을 유지한다.
// volatile: 변수를 최적화에서 제외하여 항상 메모리에 접근하도록 만

void Normal_Count(void)
{
    int count = 0;
    count++;
    printf("Normal: %d\n", count);
}

void Static_Count(void)
{
    static int count = 0;
    count++;
    printf("Static: %d\n", count);
}

void Volatile_Type(void)
{
    // value가 바뀌지 않는다는 것을 컴파일러가 알 수 있으면, 이를 최적화한다.
    // 즉, 메모리에서 값을 다시 읽지 않는다.
    // 다만, 데이터 수집 과정에서 컴파일러가 value가 바뀌지 않는다고 판단하여 최적화해
    // 기대하는 동작과 달라질 수 있음
    // 이때, volatile을 필요로 한다.

    //int value = 0;

    // 이 변수는 일반적인 코드 흐름만으로 값이 유지된다고 가정하지 말 것.
    // 해당 객체에 대한 접근을 임의로 생략하거나 값 재사용으로 대체하지 않도록 한다. 
    volatile int sensor_ready = 0;

    while (value == 0)
    {
        /* code */
    }
    
}

int main(void)
{
    const int MAX_TEMPERATURE = 80;

    // const로 선언한 일반 걕체를 수정하려고 하면 컴파일 오류가 발생한다. 
    // MAX_TEMPERATURE = 100;
    
    for (int i = 0; i < 3; i++)
    {
        Normal_Count();
    }

    for (int i = 0; i < 3; i++)
    {
        Static_Count();
    }

    Volatile_Type();

    return 0;
}
