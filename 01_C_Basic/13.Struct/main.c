#include <stdio.h>
#include "sensor.h"

int main(void)
{
    struct SensorData data = {27, 60, 3300};

    PrintSensorData(data);

    return 0;
}