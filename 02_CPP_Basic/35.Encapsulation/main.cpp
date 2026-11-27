
#include <iostream>
#include <cmath>
#include <iomanip>

class RadarTarget
{
private:
    // 외부에서 직접 접근할 수 없는 멤버
    const int targetId_;
    int x_mm_ = 0;
    int y_mm_ = 0;

    static constexpr double MAX_DISTANCE_MM = 10000.0;

public:
    // 생성자
    explicit RadarTarget(int id)
        : targetId_(id)
    {
        std::cout << "[CREATE] Target "
                  << targetId_ << '\n';
    }

    // 소멸자
    ~RadarTarget()
    {
        std::cout << "[DESTROY] Target "
                  << targetId_ << '\n';
    }

    // TODO 1
    // 목표 ID Getter
    int GetTargetId() const
    {
        return targetId_;
    }

    // TODO 2
    // X 좌표 Getter
    int GetX() const
    {
        return x_mm_;
    }

    // TODO 3
    // Y 좌표 Getter
    int GetY() const
    {
        return y_mm_;
    }

    // TODO 4
    // 좌표 변경 함수
    bool UpdatePosition(int x, int y)
    {
        // 1. std::hypot()으로 거리(mm) 계산
        double distance = std::hypot(static_cast<double>(x), static_cast<double>(y));
        // 2. 10000mm 초과라면 false 반환
        if (distance > MAX_DISTANCE_MM)
        {
            return false;
        }

        // 3. 유효하다면 x_mm_, y_mm_ 변경
        x_mm_ = x;
        y_mm_ = y;
        // 4. true 반환
        return true;
    }

    // 기존 거리 계산
    double CalculateDistance() const
    {
        return std::hypot(
                   static_cast<double>(x_mm_),
                   static_cast<double>(y_mm_)) /
               1000.0;
    }

    // TODO 5
    // 객체 정보 출력
    void PrintTarget() const
    {
        // GetTargetId(), GetX(), GetY() 사용
        std::cout << "Target ID: " << GetTargetId() << "\n";
        std::cout << "X: " << GetX() << " mm\n";
        std::cout << "Y: " << GetY() << " mm\n";

        // CalculateDistance() 사용
        std::cout << "Distance: " << CalculateDistance() << " m\n";
    }
};

int main()
{
    std::cout << std::fixed
              << std::setprecision(2);

    RadarTarget target1(1);
    RadarTarget target2(2);

    // TODO 6-1
    // target1: (300, 400)
    target1.UpdatePosition(300, 400);

    // target2: (-800, 1700)
    target2.UpdatePosition(-800, 1700);
    // 두 객체의 좌표를 변경

    std::cout << "\n[Target 1]\n";
    target1.PrintTarget();

    std::cout << "\n[Target 2]\n";
    target2.PrintTarget();

    std::cout << "\n[Invalid Update Test]\n";

    // TODO 6-2
    // target1에 (12000, 0)을 입력
    if (!(target1.UpdatePosition(12000, 0)))
    {
        std::cout << "Rejected: Position out of range" << "\n";
    }
    // 반환값이 false이면 거부 로그 출력
    

    // TODO 6-3
    // target1.PrintTarget()을 호출하여
    // 기존 좌표 (300, 400)이 유지되는지 확인
    target1.PrintTarget();

    // 아래 코드는 주석을 해제하면 컴파일 오류 발생
    // target1.x_mm_ = 5000;
    // target1.targetId_ = 99;

    return 0;
}
