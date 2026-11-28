
#include <iostream>
#include <iomanip>

class Sensor
{
public:
    // TODO 1
    // 순수 가상 함수 선언
    // 반환형: const char*
    // 함수 이름: GetName
    // const 멤버 함수
    virtual const char* GetName() const = 0;

    // TODO 2
    // 순수 가상 함수 선언
    // 반환형: void
    // 함수 이름: ReadData
    // const 멤버 함수
    virtual void ReadData() const = 0;

    // 가상 소멸자
    virtual ~Sensor() = default;
};

// 레이더 센서
class RadarSensor : public Sensor
{
private:
    double distance_m_;

public:
    explicit RadarSensor(double distance)
        : distance_m_(distance)
    {
    }

    // TODO 3
    // GetName() 재정의
    // "RadarSensor" 반환
    const char* GetName() const override
    {
        return "RadarSensor";
    }


    // TODO 4
    // ReadData() 재정의
    // Distance: 2.50 m 형태로 출력
    void ReadData() const override
    {
        std::cout << "Distance: " << distance_m_ << " m\n";
    }
};

// 온도 센서
class TemperatureSensor : public Sensor
{
private:
    double temperature_c_;

public:
    explicit TemperatureSensor(double temperature)
        : temperature_c_(temperature)
    {
    }

    // TODO 5
    // GetName() 재정의
    // "TemperatureSensor" 반환
    const char* GetName() const override
    {
        return "TemperatureSensor";
    }

    // TODO 6
    // ReadData() 재정의
    // Temperature: 26.50 C 형태로 출력
    void ReadData() const override
    {
        std::cout << "Temperature: " << temperature_c_ << " C\n";
    }
};

int main()
{
    std::cout << std::fixed
              << std::setprecision(2);

    RadarSensor radar(2.5);
    TemperatureSensor temperature(26.5);

    // 부모 클래스 포인터 배열
    Sensor *sensors[] = {
        &radar,
        &temperature};

    for (Sensor *sensor : sensors)
    {
        std::cout << "["
                  << sensor->GetName()
                  << "]\n";

        sensor->ReadData();

        std::cout << '\n';
    }

    return 0;
}
