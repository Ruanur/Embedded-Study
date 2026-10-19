#include <stdio.h>
#include "sensor.h"

int main(void)
{
    SensorData data = {27, 30, 30, SENSOR_NORMAL};
    //data.status = SENSOR_NORMAL;
    SensorData *ptr = &data;

    printf("Before\n");
    PrintSensorData(data);
    SetSensorData(ptr);

    printf("\n");

    printf("After\n");
    PrintSensorData(data);

    return 0;
}