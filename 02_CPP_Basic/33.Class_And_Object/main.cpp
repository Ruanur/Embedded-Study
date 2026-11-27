
#include <iostream>
#include <cmath>
#include <iomanip>

class RadarTarget
{
public:
    // 멤버 변수
    int x_mm = 0;
    int y_mm = 0;

    // TODO 1
    // 좌표 변경 함수
    void UpdatePosition(int x, int y)
    {
        // x_mm과 y_mm을 변경
        x_mm = x;
        y_mm = y;
    }

    // TODO 2
    // 현재 객체의 거리 계산
    double CalculateDistance() const
    {
        // x_mm, y_mm을 사용해서
        // m 단위 거리 반환
        return std::hypot(static_cast<double>(x_mm), static_cast<double>(y_mm)) / 1000.0;
    }

    // TODO 3
    // 목표물 정보 출력
    void PrintTarget() const
    {
        // X 좌표 출력
        std::cout << "X: " << x_mm << " mm\n";

        // Y 좌표 출력
        std::cout << "Y: " << y_mm << " mm\n";

        // CalculateDistance() 결과 출력
        std::cout << "Distance: " << CalculateDistance() << " m\n";
    }
};

int main()
{
    std::cout << std::fixed
              << std::setprecision(2);

    RadarTarget target1;
    RadarTarget target2;

    // TODO 4
    // target1 좌표를 (300, 400)으로 설정
    target1.UpdatePosition(300, 400);

    // target2 좌표를 (-800, 1700)으로 설정
    target2.UpdatePosition(-800, 1700);

    std::cout << "[Target 1]\n";

    // TODO 5
    // target1.PrintTarget() 호출
    target1.PrintTarget();

    std::cout << "\n[Target 2]\n";

    // TODO 6
    // target2.PrintTarget() 호출
    target2.PrintTarget();

    std::cout << "\n[Updated Target 1]\n";

    // TODO 7
    // target1의 좌표를 (600, 800)으로 변경
    target1.UpdatePosition(600, 800);
    // 변경한 정보 출력
    target1.PrintTarget();
    return 0;
}
