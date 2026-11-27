
#include <iostream>
#include <cmath> // 제곱근과 거리 계산
#include <iomanip> // 소수점 출력 형식 지정

// 레이더 목표 정보
struct RadarTarget
{
    int x_mm;
    int y_mm;
};

// TODO 1: 좌표를 직접 전달받는 거리 계산 함수
double CalculateDistance(int x_mm, int y_mm)
{
    // X/Y 좌표를 사용하여 거리 계산
    // 반환 단위는 m

    return std::hypot(static_cast<double>(x_mm), static_cast<double>(y_mm)) / 1000.0;
}

// TODO 2: 구조체를 전달받는 거리 계산 함수
double CalculateDistance(const RadarTarget &target)
{
    // 위에서 만든 CalculateDistance(int, int)
    // 함수를 호출하여 결과 반환

    return CalculateDistance(target.x_mm, target.y_mm);
}

// TODO 3: 목표 정보 출력
void PrintTarget(
    const RadarTarget &target,
    bool showDistance = true)
{
    std::cout << "X: " << target.x_mm << " mm\n";
    std::cout << "Y: " << target.y_mm << " mm\n";

    // showDistance가 true이면
    if (showDistance)
    {
        std::cout << "Distance: " << CalculateDistance(target) << " m\n";
    }
    // CalculateDistance(target)를 호출하여
    
    // 거리 정보 출력
}

int main()
{
    RadarTarget target1{300, 400};
    RadarTarget target2{-800, 1700};

    // 소수점 둘째 자리까지 출력
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "[Target 1]\n";
    PrintTarget(target1);

    std::cout << "\n[Target 2]\n";
    PrintTarget(target2, false);

    std::cout << "\n[Distance Test]\n";

    // TODO 4:
    // CalculateDistance(300, 400)를 호출하고
    // 거리 정보 출력
    std::cout << "Distance: " << CalculateDistance(300, 400) << " m\n";

    return 0;
}
