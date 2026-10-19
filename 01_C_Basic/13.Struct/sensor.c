#include <stdio.h>
#include "sensor.h"

void PrintSensorData(SensorData data)
{
    printf("Temperature: %d\n", data.temperature);
    printf("Humidity: %d\n", data.humidity);
    printf("Voltage: %d\n", data.voltage);

    switch (data.status)
    {
    case SENSOR_NORMAL:
        printf("NORMAL\n");
        break;
    
    case SENSOR_WARNING:
        printf("WARNING!\n");
        break;

    case SENSOR_ERROR:
        printf("ERROR!");
        break;

    default:
        break;
    }

}

void SetSensorData(SensorData *data)
{
    data->temperature = 30;
    data->humidity = 65;

    if (data->temperature >= 30)
    {
        data->status = SENSOR_WARNING;
    }
    else
    {
        data->status = SENSOR_NORMAL;
    }
}
