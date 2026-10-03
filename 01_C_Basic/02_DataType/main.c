#include <stdio.h>
#include <stdint.h>

void DataType()
{
    printf("char : %zu byte\n", sizeof(char));           // 1 byte
    printf("short : %zu byte\n", sizeof(short));         // 2 byte
    printf("int : %zu byte\n", sizeof(int));             // 4 byte
    printf("long : %zu byte\n", sizeof(long));           // 4 byte
    printf("long long : %zu byte\n", sizeof(long long)); // 8 byte

    printf("float : %zu byte\n", sizeof(float));   // 4 byte
    printf("double : %zu byte\n", sizeof(double)); // 8 byte

    // sizeof()의 결과값이 왜 %zu인가?
    // sizeof의 return 값 -> size_t
    // size_t는 부호 없는 정수형(unsigned integer), 메모리 크기는 음수가 될 수 없음.

    // z: 부호 없는 정수형의 크기가 size_t와 같음을 나타내는 길이 수정자
    // u: 부호 없는 정수(unsigned)를 출력하라는 의미
    // sizeof -> size_t -> %zu

    return;
}

void Signed_Unsigned_Type()
{
    signed char a = 127;
    signed char b = -128;

    unsigned char c = 255;
    unsigned char d = 0;

    printf("signed char max : %d\n", a); // 127
    printf("signed char min : %d\n", b); // -128

    printf("unsigned char max : %u\n", c); // 255
    printf("unsigned char min : %u\n", d); // 0

    return;

    // signed char / unsigned char는 동일하게 8 bit를 가짐 = 256가지 값 표현 가능
    // signed char range = -128 ~ 127
    // unsigned char range = 0 ~ 255

    // unsigned char :
    // 00000000 = 0, 00000001 = 1 ... 11111110 = 254, 11111111 = 255

    // signed char :
    // -128 ... -1 | 0 ... 127 -> 2의 보수 표현 사용
    // 127 = 01111111
    // 0 = 00000000
    // -1 = 11111111
    // -128 = 10000000
}

void Practical()
{

    printf("uint8_t  : %zu byte\n", sizeof(uint8_t));  // 1 byte
    printf("uint16_t : %zu byte\n", sizeof(uint16_t)); // 2 byte
    printf("uint32_t : %zu byte\n", sizeof(uint32_t)); // 4 byte
    printf("uint64_t : %zu byte\n", sizeof(uint64_t)); // 8 byte

    printf("int8_t   : %zu byte\n", sizeof(int8_t));  // 1 byte
    printf("int16_t  : %zu byte\n", sizeof(int16_t)); // 2 byte
    printf("int32_t  : %zu byte\n", sizeof(int32_t)); // 4 byte
    printf("int64_t  : %zu byte\n", sizeof(int64_t)); // 8 byte

    uint8_t value = 255;
    printf("value = %u\n", value);

    value = value + 1;
    printf("value = %u\n", value);

    // uint8_t = 8비트, 0~255의 범위를 가진다.
    // value가 256이 되면? -> overflow 발생
    // 
    // 255 = 11111111
    //      +       1
    //      100000000 = 256
    // 8비트만 저장하기 때문에 앞의 1이 저장되지 않는다
    // 00000000 = 0
    // 따라서 value = 256일 때 0 출력됨
    // 포함되지 않은 1. 즉, 상위 비트는 메모리에 남아있는게 아닌 들어갈 공간이 없어 잘렸다고 본다.
    return;
}

int main(void)
{
    char input;
    while (1)
    {
        printf("[DataType List] : A.Data Type  B.Signed_Unsigned Type  C.Practical Q. Quit\n");
        printf("Select : ");

        scanf(" %c", &input);
        switch (input)
        {
        case 'A':
            DataType();
            break;

        case 'B':
            Signed_Unsigned_Type();
            break;

        case 'C':
            Practical();
            break;

        case 'Q':
            return 0;
            
        default:
            break;
        }
    }

    return 0;
}