#include <iostream>

using namespace std;

// 장비 설정 구조체
struct DeviceConfig
{
    int warningThreshold;
    int samplingIntervalMs;
};

// TODO 1
// 참조자를 통해 경고 기준값 변경
void UpdateThreshold(
    DeviceConfig &config,
    int newThreshold)
{
    // newThreshold가 0보다 큰 경우에만
    if (newThreshold > 0)
    {
        // config.warningThreshold 변경
        config.warningThreshold = newThreshold;
    }
    
}

// TODO 2
// 경고 조건 검사
bool IsWarning(
    int sensorValue,
    const DeviceConfig &config)
{
    // sensorValue가 warningThreshold 이상이면
    // true, 아니면 false 반환
    return sensorValue >= config.warningThreshold;
    
}

// TODO 3
// 장비 설정 출력
void PrintConfig(const DeviceConfig &config)
{
    // warningThreshold 출력
    cout << "WARNING Threshold: " << config.warningThreshold << "\n";

    // samplingIntervalMs 출력
    cout << "Interval Ms: " << config.samplingIntervalMs << "\n";
    
}

int main()
{
    DeviceConfig config{30, 100};

    cout << "[Initial Config]\n";
    PrintConfig(config);

    UpdateThreshold(config, 35);

    cout << "\n[Updated Config]\n";
    PrintConfig(config);

    int sensorValues[] = {20, 34, 35, 40};

    size_t values_length = sizeof(sensorValues) / sizeof(sensorValues[0]);

    // TODO 4
    // 반복문으로 모든 센서값 검사
    for (size_t i = 0; i < values_length; i++)
    {
        cout << "[SENSOR] " << sensorValues[i] << " -> ";
        // IsWarning()을 호출하고
        // WARNING 또는 NORMAL 출력
        if (IsWarning(sensorValues[i], config))
        {
            cout << "WARNING\n";
        }
        else
        {
            cout << "NORMAL\n";
        }
    }


    return 0;

    // 예상 동작 수행
    // 1. 장비 초기 설정을 출력한다.
    // 2. 경고 기준값을 30에서 35로 변경한다.
    // 3. 센서값 20, 34, 35, 40을 순서대로 검사한다.
    // 4. 경고 기준 이상이면 WARNING, 미만이면 NORMAL을 출력한다.
}