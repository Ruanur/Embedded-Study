#include <stdio.h>
#include "sensor.h"

void PrintSensorData(struct SensorData data)
{
    printf("Temperature: %d\n", data.temperature);
    printf("Humidity: %d\n", data.humidity);
    printf("voltage: %d\n", data.voltage);
}