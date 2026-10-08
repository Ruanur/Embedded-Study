#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t data[3] = {10, 20, 30};
    uint8_t *ptr = &data[0];

    // ptr: 첫 번째 요소의 주소
    // *ptr : 첫 번쨰 요소의 값
    // ptr + 1: 다음 요소를 가리키는 주소
    // *(ptr + 1): 다음 요소의 값
    // *(ptr + 2): 세 번째 요소의 값

    printf("Data[0] = %u\n", data[0]);
    printf("*ptr = %u\n", *ptr);

    printf("Data[0] = %u\n", data[1]);
    printf("*ptr = %u\n", *(ptr + 1));

    printf("Data[0] = %u\n", data[2]);
    printf("*ptr = %u\n", *(ptr + 2));

    // uint8_t는 1 Byte, 주소가 1 Byte씩 이동
    // 포인터 연산은 가리키는 자료형의 크기를 기준으로 이동한다.
    // Ex. int의 경우 4 Byte씩 이동
    printf("ptr = %p\n", (void *)ptr); // 출력값 : 00000000005FFE75
    printf("ptr + 1 = %p\n", (void *)(ptr + 1)); // 출력값 : 00000000005FFE76
    printf("ptr + 2 = %p\n", (void *)(ptr + 2)); // 출력값 : 00000000005FFE77


    // 포인터로 배열 값 변경
    uint8_t data_cp[3] = {10, 20, 30};
    uint8_t *ptr_cp = data_cp;

    *(ptr_cp + 1) = 99;

    printf("%u\n", data_cp[0]);
    printf("%u\n", data_cp[1]); // 99
    printf("%u\n", data_cp[2]);

    return 0;
}