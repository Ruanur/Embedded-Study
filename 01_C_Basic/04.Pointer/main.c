#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /*
    value -> 값
    &value -> value의 주소

    ptr -> 저장하고 있는 주소
    *ptr -> ptr이 가리키는 주소의 값
    */
    int value = 10;
    int *ptr = &value;

    // ptr에 value의 주소를 저장한다.
    //
    //     value
    // ┌────────────┐
    // │ 10     │
    // └────────────┘
    //       ↑
    //       │
    //         &value
    //       │
    // ┌────────────┐
    // │ 주소    │
    // └────────────┘
    //      ptr

    printf("Value = %d\n", value);
    printf("Value's Address = %p\n", (void*)&value);
    printf("Pointer(*int) = %p\n", (void *)ptr);
    printf("Pointer = %d\n", *ptr);

    /*
        value == 10
        *ptr == 10

        &value == ptr
    */

    // 포인터를 이용한 값 변경
    *ptr = 100;
    printf("Changed Value by a Pointer: %d\n", value);

    // 다른 자료형을 가리킨다면?
    //  uint8_t *ptr_int8 = &value;
    // -> Error: initialization of 'uint8_t *' {aka 'unsigned char *'}
    //           from incompatible pointer type 'int *'
    // 서로 다른 자료형은 일반적으로 호환되지 않는다
    // 다만, 형변환을 통한 접근이 가능
    // Ex. uint8_t *ptr = (uint8_t *)&value;

    uint8_t value_int8 = 10;
    uint8_t *ptr_int8 = &value_int8;

    printf("uint8_t Value = %u\n", *ptr_int8);

    // 배열과 포인터 연결
    uint8_t data[3] = {10, 20, 30};
    uint8_t *array_ptr = &data[0];

    printf("Array Pointer = %u\n", *array_ptr);
    
    // 배열 주소 확인
    // 배열 요소는 연속된 메모리에 저장됨
    // uint8_t의 크기가 1 Byte이므로 인접한 요소의 주소 차이가 1 Byte이다.

    printf("Array Address.0 = %p\n", (void *)&data[0]); // 실행 결과값 : 00000000005FFE60
    printf("Array Address.1 = %p\n", (void *)&data[1]); // 실행 결과값 : 00000000005FFE61
    printf("Array Address.2 = %p\n", (void *)&data[2]); // 실행 결과값 : 00000000005FFE62

    printf("sizeof(data[0]) = %zu\n", sizeof(data[0]));
    printf("sizeof(data[1]) = %zu\n", sizeof(data[1]));
    printf("sizeof(data[2]) = %zu\n", sizeof(data[2]));

    // 자료형 포인터와 크기의 상관관계
    // int * -> int를 가리키는 포인터
    // uint8_t * -> uint8_t를 가리키는 포인터
    // sizeof(int*) -> int 포인터 자체의 크기
    // sizeof(uint8_t*) -> uint8_t 포인터 자체의 크기
    // sizeof(int) -> int 데이터의 크기
    // sizeof(uint8_t) -> uint8_t 데이터의 크기

    printf("sizeof(int *) = %zu\n", sizeof(int*));
    printf("sizeof(uint8_t*) = %zu\n", sizeof(uint8_t*));
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(uint8_t) = %zu\n", sizeof(uint8_t));
    return 0;

}