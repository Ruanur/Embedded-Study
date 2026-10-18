#include <stdio.h>
#include "sensor.h"

int main(void)
{
    struct SensorData data = {27, 60, 3300};
    struct SensorData *ptr = &data;

    printf("Before\n");
    PrintSensorData(data);
    SetSensorData(ptr);

    printf("\n");

    printf("After\n");
    PrintSensorData(data);

    return 0;
}