#ifndef SENSOR_H
#define SENSOR_H

typedef enum
{
    SENSOR_NORMAL,
    SENSOR_WARNING,
    SENSOR_ERROR
} SensorStatus;

typedef struct 
{
    int temperature; // 온도
    int humidity; // 습도
    int voltage; // 전압
    SensorStatus status;
} SensorData;

void PrintSensorData(SensorData data);
void SetSensorData(SensorData *data);

#endif
