#include <stdio.h>
#include <stdint.h>

#define BUTTON_PIN (1u << 3) //00001000
#define LED_PIN (1u << 5) // 00100000

#define GPIO_MODE_INPUT 0u
#define GPIO_MODE_OUTPUT 1u

typedef struct
{
    uint32_t MODER;
    uint32_t IDR;
    uint32_t ODR;
} GPIO_Registers;

// GPIO 핀 모드 설정
void GPIO_SetMode(volatile GPIO_Registers *gpio, uint32_t pinNumber, uint32_t mode)
{
    // TODO:
    // 1. 비트 위치 계산
    uint32_t shift = pinNumber * 2; 
    uint32_t mask = 3u << shift;    
    // 2. 기존 2비트 삭제
    gpio->MODER &= ~mask;
    // 3. 새로운 모드 설정
    gpio->MODER |= (mode << shift);
}

// 출력 비트 설정
void GPIO_SetPin(volatile GPIO_Registers *gpio, uint32_t pin)
{
    // TODO: LED 켜기
    gpio->ODR |= pin;
}

// 출력 비트 해제
void GPIO_ClearPin(volatile GPIO_Registers *gpio, uint32_t pin)
{
    gpio->ODR &= ~pin;
}

// 입력 레지스터 읽기
int GPIO_ReadInput(const volatile GPIO_Registers *gpio, uint32_t pin)
{
    // TODO: IDR 비트 검사
    return (gpio->IDR & pin) ? 1 : 0;
}

// 버튼 상태에 따른 LED 제어
void UpdateLED(volatile GPIO_Registers *gpio)
{
    // TODO: GPIO_ReadInput() 사용
    int button = GPIO_ReadInput(gpio, BUTTON_PIN);

    if (button)
    {
        // TODO: 버튼이 눌렸으면 LED 켜기
        GPIO_SetPin(gpio, LED_PIN);
    }
    else
    {
        // TODO: 버튼을 떼었으면 LED 끄기
        GPIO_ClearPin(gpio, LED_PIN);
    }
}

int main(void)
{
    volatile GPIO_Registers gpioA = {0};

    // TODO: Pin 3 입력 모드 설정
    GPIO_SetMode(&gpioA, 3, GPIO_MODE_INPUT);

    // TODO: Pin 5 출력 모드 설정
    GPIO_SetMode(&gpioA, 5, GPIO_MODE_OUTPUT);

    // 1. 버튼을 누르지 않은 상태
    gpioA.IDR &= ~BUTTON_PIN;
    UpdateLED(&gpioA);

    // TODO: IDR 및 ODR 출력
    printf("[Button Released]\n");
    printf("IDR: 0x%08X\n",(unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");
    // 2. 버튼을 누른 상태
    gpioA.IDR |= BUTTON_PIN;
    UpdateLED(&gpioA);

    // TODO: IDR 및 ODR 출력
    printf("[Button Pressed]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");

    // 3. 버튼을 다시 뗀 상태
    gpioA.IDR &= ~BUTTON_PIN;
    UpdateLED(&gpioA);

    // TODO: IDR 및 ODR 출력
    printf("[Button Released]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    return 0;
}