#include <stdio.h>
#include <stdint.h>

#define BUTTON_PIN (1u << 3)
#define LED_PIN (1u << 5)

#define GPIO_MODE_INPUT 0u
#define GPIO_MODE_OUTPUT 1u

#define DEBOUNCE_MS 30u

typedef struct
{
    uint32_t MODER;
    uint32_t IDR;
    uint32_t ODR;
} GPIO_Registers;

typedef struct
{
    int lastRawState;
    int stableState; // 안정된 것으로 확정한 버튼값
    uint32_t lastChangeMs;
} DebounceState;

typedef struct
{
    uint32_t timeMs;
    int pressed;
} ButtonSample;

// Day 21 함수 재사용
void GPIO_SetMode(
    volatile GPIO_Registers *gpio,
    uint32_t pinNumber,
    uint32_t mode)
{
    // TODO
    // 1. 비트 위치 계산
    uint32_t shift = pinNumber * 2; // 10
    uint32_t mask = 3u << shift;    // 00 00 11 00 00 00 00 00
    // 2. 기존 2비트 삭제
    gpio->MODER &= ~mask;
    // 3. 새로운 모드 설정
    gpio->MODER |= (mode << shift);
}

// Day 22 함수 재사용
int GPIO_ReadInput(
    const volatile GPIO_Registers *gpio,
    uint32_t pin)
{
    // TODO
    return (gpio->IDR & pin) ? 1 : 0;
}

// Day 23 함수 재사용
void GPIO_TogglePin(
    volatile GPIO_Registers *gpio,
    uint32_t pin)
{
    // TODO
    gpio->ODR ^= pin;
}

// 오늘의 핵심 함수
void UpdateDebouncedButton(
    volatile GPIO_Registers *gpio,
    DebounceState *state,
    uint32_t nowMs)
{
    // TODO: 현재 입력 읽기
    int currentButton = GPIO_ReadInput(gpio, BUTTON_PIN);

    // TODO: 원시 입력 변경 감지 및 시간 기록
    if (currentButton != state->lastRawState)
    {
        state->lastRawState = currentButton;
        state->lastChangeMs = nowMs;
    }

    // TODO: 안정 시간 검사
    uint32_t elapsed = nowMs - state->lastChangeMs;

    // TODO: 안정 상태 갱신
    // 시간 조건 && 상태 변경 조건 
    if (elapsed >= DEBOUNCE_MS && currentButton != state->stableState)
    {
        // TODO: StableState 갱신
        state->stableState = currentButton;
        // 안정 상태가 1로 확정되었다면
        if (state->stableState == 1)
        {
            // TODO: 상승 엣지일 때 LED 토글
            GPIO_TogglePin(gpio, LED_PIN);
        }
    }
}

int main(void) 
{
    volatile GPIO_Registers gpioA = {0};
    DebounceState buttonState = {0};

    GPIO_SetMode(&gpioA, 3, GPIO_MODE_INPUT);
    GPIO_SetMode(&gpioA, 5, GPIO_MODE_OUTPUT);

    ButtonSample samples[] =
        {
            {0, 0}, 
            {10, 1}, 
            {12, 0}, 
            {14, 1}, 
            {20, 1}, 
            {44, 1}, 
            {100, 0}, 
            {102, 1}, 
            {104, 0}, 
            {135, 0}, 
            {180, 1}, 
            {211, 1}
        };

    size_t count = sizeof(samples) / sizeof(samples[0]);

    for (size_t i = 0; i < count; i++)
    {
        // TODO 1: samples[i].pressed 값을
        //         gpioA.IDR에 반영
        if (samples[i].pressed)
        {
            gpioA.IDR |= BUTTON_PIN;
        }
        else
        {
            gpioA.IDR &= ~BUTTON_PIN;
        }

        // TODO 2: UpdateDebouncedButton() 호출
        UpdateDebouncedButton(&gpioA, &buttonState, samples[i].timeMs);

        // TODO 3: 시간, IDR, ODR 출력
        printf("Time: %3ums | IDR: 0x%08X | ODR: 0x%08X\n",
            (unsigned)samples[i].timeMs,
            (unsigned)gpioA.IDR,
            (unsigned)gpioA.ODR);
    }

    return 0;
}