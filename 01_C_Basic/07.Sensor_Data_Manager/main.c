#include <stdio.h>
#include <stdint.h>

void Sensor_Data()
{
    uint8_t Sensor_Data_List[20] =
    {
        29, 27, 32, 28, 31,
        24, 23, 22, 20, 26,
        33, 30, 21, 25, 24,
        27, 28, 32, 30, 26
    };

    size_t count = sizeof(Sensor_Data_List) / sizeof(Sensor_Data_List[0]);

    int sum = 0;
    int data_up_count = 0;
    
    for (size_t i = 0; i < count; i++)
    {
        sum += Sensor_Data_List[i];

        if (Sensor_Data_List[i] >= 25)
        {
            data_up_count++;
        }
    }

    printf("Count Result_25'C: %d\n", data_up_count);

    float Warning = (float)sum / count;

    if (Warning >= 28)
    {
        printf("WARNING");
    }
    else
    {
        printf("Avg temperature: %.2f\n", Warning);
    }
}

int main(void)
{
    uint8_t temperature[10] = 
    {
        25, 27, 26, 28, 24,
        29, 30, 26, 27, 25
    };

    size_t count = sizeof(temperature) / sizeof(temperature[0]);
    int sum = 0;
    uint8_t min = temperature[0];
    uint8_t max = temperature[0];

    printf("Sensor Count = %zu\n", count);

    for (size_t i = 0; i < count; i++)
    {
        printf("Temperature[%zu] = %u\n", i, temperature[i]);

        sum += temperature[i];

        if (min > temperature[i])
        {
            min = temperature[i];
        }
        if (max < temperature[i])
        {
            max = temperature[i];
        }
    }

    float avg = (float)sum / count;

    printf("Avg = %.1f\n", avg);
    printf("Min = %u\n", min);
    printf("Max = %u\n", max);

    printf("Sum = %d\n", sum);

    printf("Array Size = %zu bytes\n", sizeof(temperature));
    printf("Element Size = %zu bytes\n", sizeof(temperature[0]));
    printf("Element Count = %zu\n", count);

    Sensor_Data();

    return 0;
}