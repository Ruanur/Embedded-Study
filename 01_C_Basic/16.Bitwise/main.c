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

uint8_t flags = 0;

void Warning_set(SensorData data)
{

    if (data.temperature >= 30)
    {
        flags |= FLAG_TEMP_WARNING;
    }
    else
    {
        flags &= ~FLAG_TEMP_WARNING;
    }

    if (data.humidity >= 70)
    {
        flags |= FLAG_HUMID_WARNING;
    }
    else
    {
        flags &= ~FLAG_HUMID_WARNING;
    }
}

void Print_Warning()
{
    if ((flags & FLAG_TEMP_WARNING) != 0)
    {
        printf("Temperature Warning!\n");
    }

    if ((flags & FLAG_HUMID_WARNING) != 0)
    {
        printf("Humidity Warning!\n");
    }

    if ((flags & (FLAG_TEMP_WARNING | FLAG_HUMID_WARNING)) == 0)
    {
        printf("All Sensors Normal\n");
    }
}

int main()
{
    SensorData data = {33, 95, 2200};
    Warning_set(data);
    printf("Flags: %u\n", flags);
    Print_Warning();

    data = (SensorData){25, 50, 2200};
    Warning_set(data);
    printf("Flags: %u\n", flags);
    Print_Warning();

    data = (SensorData){33, 50, 2200};
    Warning_set(data);
    printf("Flags: %u\n", flags);
    Print_Warning();

    data = (SensorData){25, 95, 2200};
    Warning_set(data);
    printf("Flags: %u\n", flags);
    Print_Warning();

    data = (SensorData){33, 95, 2200};
    Warning_set(data);
    printf("Flags: %u\n", flags);
    Print_Warning();

    return 0;
}
