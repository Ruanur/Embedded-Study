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
    printf("Pointer(*void) = %p\n", (void *)ptr);
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
    // 서로 다른 자료형은 가리킬 수 없음

    uint8_t value_int8 = 10;
    uint8_t *ptr_int8 = &value_int8;

    printf("uint8_t Value = %u\n", *ptr_int8);

    // 배열과 포인터 연결
    uint8_t data[3] = {10, 20, 30};
    uint8_t *array_ptr = &data[0];

    printf("Array Pointer = %u\n", *array_ptr);
    
    // 배열 주소 확인
    // uint8_t는 1 Byte이므로 주소가 1 Byte씩 차이가 난다.

    printf("Array Address.0 = %p\n", (void *)&data[0]); // 00000000005FFE60
    printf("Array Address.1 = %p\n", (void *)&data[1]); // 00000000005FFE61
    printf("Array Address.2 = %p\n", (void *)&data[2]); // 00000000005FFE62

    return 0;

}