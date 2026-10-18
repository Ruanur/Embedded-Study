#ifndef SENSOR_H
#define SENSOR_H

struct SensorData
{
    int temperature; // 온도
    int humidity; // 습도
    int voltage; // 전압
};

void PrintSensorData(struct SensorData data);
void SetSensorData(struct SensorData *data);


#endif
