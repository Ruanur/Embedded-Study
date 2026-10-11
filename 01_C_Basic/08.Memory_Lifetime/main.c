#include <stdio.h>

int global_count;

int TestFunction(void)
{
    // 전역 변수(Global Variable) vs 지역 변수 (Local Variable)
    // 지역 변수 (Local Variable): 선언된 블록 내부에서만 접근 가능, 블록을 벗어나면 사용 불가
    //                 해당 블록이나 함수에 진입할 때 생성되고, 블록이 종료될 때 메모리에서 소멸
    // 전역 변수(Global Variable): 프로그램 전체에서 어디서든 접근하고 사용할 수 있음
    //                            프로그램이 시작될 때 메모리에 생성, 프로그램이 완전히 종료될 때 소멸 

    // int local_count: 블록에 진입할 때 초기화되고, 블록의 실행이 끝나면 수명이 종료됨.
    // static int local_count: 프로그램 실행동안 수명이 유지되고, 초기화는 한 번만 수행됨.
    //                         이름의 접근 범위는 선언된 블록으로 제한된다.
    static int local_count = 0;

    local_count++;
    global_count++;

    printf("Local: %d, Local Address: %p\n", local_count, (void *)&local_count);
    printf("Global: %d, Global Address: %p\n", global_count, (void *)&global_count);

    return local_count;
}

int main(void)
{
    // 지역 변수는 함수 종료 시 소멸됨, 3번 호출하더라도 동일한 결과가 나타남
    // 전역 변수는 프로그램 완전히 종료 시 소멸됨, 함수가 종료되더라도 변수 저장됨 
    TestFunction(); // Local: 1, Global: 1
    TestFunction(); // Local: 1, Global: 2
    TestFunction(); // Local: 1, Global: 3

    // printf("%d\n", local_count);
    // ERROR! identifier "local_count" is undefined
    // static은 변수의 생명주기를 바꾸지만,
    // 변수를 사용할 수 있는 범위(Scope)까지 함수 밖으로 확장하지는 않는다.

    int result = TestFunction();

    printf("Returned Value: %d\n", result);

    return 0;
}