#include <stdio.h>
#include <stdint.h>

#define FLAG_TEMP_WARNING (1u << 0) // 00000001
#define FLAG_HUMID_WARNING (1u << 1) // 00000010 
#define FLAG_SENSOR_ERROR (1u << 2) // 00000100

typedef struct
{
    int temperature; // 온도
    int humidity;    // 습도
    int voltage;     // 전압
} SensorData;

void SetFlag(uint8_t *flags, uint8_t mask)
{
    //TODO: 비트 설정
    *flags |= mask;
}

void ClearFlag(uint8_t *flags, uint8_t mask)
{
    *flags &= (uint8_t)~mask;
}

int IsFlagSet(uint8_t flags, uint8_t mask)
{
    //TODO: 비트 확인 결과 반환
    return (flags & mask) != 0;
}

void Warning_set(SensorData data, uint8_t *flags)
{

    // TODO: 온도 및 습도에 따른
    // SetFlag / ClearFlag 호출

    if (data.temperature >= 30)
    {
        SetFlag(flags, FLAG_TEMP_WARNING);
    }
    else
    {
        ClearFlag(flags, FLAG_TEMP_WARNING);
    }

    if (data.humidity >= 70)
    {
        SetFlag(flags, FLAG_HUMID_WARNING);
    }
    else
    {
        ClearFlag(flags, FLAG_HUMID_WARNING);
    }
}

void Print_Warning(uint8_t flags)
{
    if (IsFlagSet(flags, FLAG_TEMP_WARNING))
    {
        printf("Temperature Warning!\n");
    }

    if (IsFlagSet(flags, FLAG_HUMID_WARNING))
    {
        printf("Humidity Warning!\n");
    }

    if (!IsFlagSet(flags, (FLAG_TEMP_WARNING | FLAG_HUMID_WARNING)))
    {
        // 00000011 : 3 - flag
        // 
        // 00000001 
        // 00000010 OR
        // 00000011 : 3 - mask
        printf("All Sensors Normal\n");
    }
}

int main()
{
    uint8_t flags = 0;

    SensorData data = {33, 95, 2200};
    Warning_set(data, &flags);
    printf("Flags: %u\n", flags);
    Print_Warning(flags);

    return 0;
}
