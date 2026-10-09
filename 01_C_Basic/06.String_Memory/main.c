#include <stdio.h>
#include <string.h>
#include <stdint.h>

void Sensor_buffer()
{
    uint8_t packet[5] =
    {
        0xAA, // 헤더
        0x01, // 명령어
        0x10, // 데이터 1
        0x20, // 데이터 2
        0x00 // 체크섬 자리, 임시로 0 설정
    };

    uint8_t buffer[5];
    char temp[] = "TEMP";

    for (size_t i = 0; i < sizeof(packet); i++)
    {
        printf("%u ", packet[i]);
    }

    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, packet, sizeof(packet));
    
    printf("\n");
    if (memcmp(buffer, packet, sizeof(packet)) == 0)
    {
        printf("Packet Copy: Same\n");
    }
    else
    {
        printf("Packet Copy: Different\n");
    }

    printf("\n");
    printf("TEMP Length = %zu\n", strlen(temp));
    printf("TEMP Memory Size = %zu\n", sizeof(temp));
    if (strlen(temp) == sizeof(temp))
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }
}

int main(void)
{
    // 길이는 5인데 메모리 크기는 6인 이유
    // C 문자열은 끝에 문자열의 끝을 표시하는 널 문자 \0를 저장하기 때문
    // H E L L O \0
    // 0 1 2 3 4 5
    char text[] = "HELLO";

    // 첫 번째 요소를 가리키는 포인터로 변환된다.
    // 이 때, char text[] = "HELLO" 와 char *ptr = text는 같은 개념이 아니다.
    // text[]는 배열에 문자열을 저장, *ptr는 그 배열의 첫 번째 요소를 가리킴
    char *ptr = text;

    uint8_t buffer[5];

    // memset() - 메모리를 특정 값으로 채우기
    // 이는 센서 버퍼나 통신 버퍼를 초기화 할 때 응용 가능.
    memset(buffer, 0, sizeof(buffer));

    for(size_t i = 0; i < sizeof(buffer); i++)
    {
        printf("%u ", buffer[i]);
    }

    uint8_t source[4] = {10, 20, 30, 40};
    uint8_t destination[4];

    memcpy(destination, source, sizeof(source));

    printf("\n");
    printf("Text = %s\n", text);
    printf("Length = %zu\n", strlen(text));
    printf("Memory Size = %zu\n", sizeof(text));

    printf("%s\n", text); 
    printf("%s\n", ptr);
    printf("%c\n", *ptr); // 결과값 : H
    printf("%c\n", *(ptr + 1)); // 결과값 : E


    uint8_t a[3] = {10, 20, 30};
    uint8_t b[3] = {10, 20, 30};

    // memcmp() - 메모리 비교 함수
    // 반환값이 0이면 두 메모리 영역이 같다는 의미를 가짐
    if (memcmp(a, b, sizeof(a)) == 0)
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }

    Sensor_buffer();

    return 0;
}