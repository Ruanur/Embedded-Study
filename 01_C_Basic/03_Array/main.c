#include <stdio.h>
#include <stdint.h>

// uint8_t -> 1 Byte, 배열에 각각 1 Byte씩 저장됨
uint8_t temperature[5] = {25, 27, 26, 28, 24};

void Sensor_Data()
{
    // 예제: 센서 데이터 처리
    int sum = 0;
    uint8_t max = temperature[0];
    uint8_t min = temperature[0];
    size_t count = sizeof(temperature) / sizeof(temperature[0]);

    printf("========================\n");
    printf("Sensor Data\n");
    printf("\n");

    for (int i = 0; i < count; i++)
    {
        printf("Data.%d = %u\n", i, temperature[i]);
        sum += temperature[i];
        if (temperature[i] < min)
        {
            min = temperature[i];
        }
        if (temperature[i] > max)
        {
            max = temperature[i];
        }
    }

    printf("========================\n");
    printf("Sum = %d\n", sum);
    printf("Average = %d\n", sum / count);
    printf("Min = %d\n", min);
    printf("Max = %d\n", max);
    printf("========================\n");

    printf("Array Size = %zu byte\n", sizeof(temperature));
    printf("Element Size = %zu byte\n", sizeof(temperature[0]));
    printf("Element Count = %zu\n", count);
    printf("========================\n");
}

int main(void)
{
    uint8_t data[10]; // 1 Byte
    uint16_t data_16[10]; // 2 Byte
    uint32_t data_32[10]; // 4 Byte

    //자료형 하나의 크기가 달라지면 
    //배열 전체가 사용하는 메모리 크기도 달라진다.
    
    printf("========================\n");
    printf("uint8 Data = %zu byte\n", sizeof(data));
    printf("uint16 Data = %zu byte\n", sizeof(data_16));
    printf("uint32 Data = %zu byte\n", sizeof(data_32));
    printf("\n");

    Sensor_Data();

    return 0;
}