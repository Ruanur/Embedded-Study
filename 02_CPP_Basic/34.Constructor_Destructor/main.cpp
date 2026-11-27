
#include <iostream>
#include <cmath>
#include <iomanip>

class RadarTarget
{
public:
    int targetId;
    int x_mm;
    int y_mm;

    // TODO 1
    // 기본 생성자
    // targetId = 0
    // x_mm = 0
    // y_mm = 0
    // 멤버 초기화 리스트를 사용
    RadarTarget()
        : targetId(0), x_mm(0), y_mm(0)
    {
        // [CREATE] Target 0 출력
        std::cout << "[CREATE] Target " << targetId << "\n";
    }

    // TODO 2
    // 매개변수 생성자
    RadarTarget(int id, int x, int y)
        : targetId(id), x_mm(x), y_mm(y)
    {
        // [CREATE] Target ID 출력
        std::cout << "[CREATE] Target " << targetId << "\n";
    }

    // TODO 3
    // 소멸자
    ~RadarTarget()
    {
        // [DESTROY] Target ID 출력
        std::cout << "[DESTROY] Target " << targetId << "\n";
    }

    // 기존 좌표 변경 함수
    void UpdatePosition(int x, int y)
    {
        x_mm = x;
        y_mm = y;
    }

    // 기존 거리 계산 함수
    double CalculateDistance() const
    {
        return std::hypot(
                   static_cast<double>(x_mm),
                   static_cast<double>(y_mm)) /
               1000.0;
    }

    // TODO 4
    // ID, X, Y, 거리 출력
    void PrintTarget() const
    {
        std::cout << "\n";
        std::cout << "[Target " << targetId << "]" << '\n';
        // Target ID
        std::cout << "Target ID: " << targetId << "\n";

        // X 좌표 (mm)
        std::cout << "X: " << x_mm << " mm\n";

        // Y 좌표 (mm)
        std::cout << "Y: " << y_mm << " mm\n";

        // 거리 (m)
        std::cout << "Distance: " << CalculateDistance() << " m\n\n";
    }
};

int main()
{
    std::cout << std::fixed
              << std::setprecision(2);

    // 기본 생성자
    RadarTarget defaultTarget;

    // 매개변수 생성자
    RadarTarget target1(1, 300, 400);

    target1.PrintTarget();
    target1.UpdatePosition(1200, 700);
    
    std::cout << "\n[After Position Update]\n";
    target1.PrintTarget();

    RadarTarget target2(2, -800, 1700);

    // TODO 5
    // target1 좌표를 (300, 400)으로 변경
    
    // target1과 target2의 정보 출력
    
    target2.PrintTarget();


    std::cout << "\n[Inner Scope]\n";

    {
        // TODO 6
        // target3 객체 생성
        // ID = 3
        // X = 600
        // Y = 800
        RadarTarget target3(3, 600, 800);
        
        // target3 정보 출력
        target3.PrintTarget();
    }

    std::cout << "\n[Main End]\n";

    return 0;
}
