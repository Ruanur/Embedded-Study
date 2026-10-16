#include <stdio.h>
#include "sensor.h"

int GetTemperature(void)
{
    return 27;
}

int GetAverageTemperature(int temperatures[], int temperatures_size)
{
    int sum = 0;
    int *ptr = &temperatures[0];
    int average = 0;

    for (int i = 0; i < temperatures_size; i++)
    {
        sum += *(ptr + i);
    }

    average = sum / temperatures_size;

    return average;
    
}