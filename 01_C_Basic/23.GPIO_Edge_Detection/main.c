#include <stdio.h>
#include <stdint.h>

#define BUTTON_PIN (1u << 3) // 버튼: Pin 3
#define LED_PIN (1u << 5) // LED: Pin 5

#define GPIO_MODE_INPUT 0u
#define GPIO_MODE_OUTPUT 1u

typedef struct
{
    uint32_t MODER;
    uint32_t IDR;
    uint32_t ODR;
} GPIO_Registers;

void GPIO_SetMode(
    volatile GPIO_Registers *gpio,
    uint32_t pinNumber,
    uint32_t mode)
{
    uint32_t shift = pinNumber * 2; 
    uint32_t mask = 3u << shift;    

    gpio->MODER &= ~mask;
    gpio->MODER |= (mode << shift);
}

int GPIO_ReadInput(
    const volatile GPIO_Registers *gpio,
    uint32_t pin)
{
    return (gpio->IDR & pin) ? 1 : 0;
}

void GPIO_TogglePin(
    volatile GPIO_Registers *gpio,
    uint32_t pin)
{
    gpio->ODR ^= pin;
}

void UpdateLED(
    volatile GPIO_Registers *gpio,
    int *previousButton)
{
    // TODO: 현재 버튼 상태 확인
    int currentButton = GPIO_ReadInput(gpio, BUTTON_PIN);
    // TODO: 상승 엣지 감지 후 LED 토글
    if (*previousButton == 0 && currentButton == 1)
    {
        GPIO_TogglePin(gpio, LED_PIN);
    }
    // TODO: 이전 상태 갱신

    *previousButton = currentButton;
}

int main(void)
{
    volatile GPIO_Registers gpioA = {0};
    int previousButton = 0;

    // TODO: 버튼 입력 모드 설정
    GPIO_SetMode(&gpioA, 3, GPIO_MODE_INPUT);
    // TODO: LED 출력 모드 설정
    GPIO_SetMode(&gpioA, 5, GPIO_MODE_OUTPUT);

    // 1. 초기 상태: 버튼 OFF
    gpioA.IDR &= ~BUTTON_PIN;
    UpdateLED(&gpioA, &previousButton);
    printf("[Initial]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");
    
    // 2. 버튼 누름
    gpioA.IDR |= BUTTON_PIN;
    UpdateLED(&gpioA, &previousButton);
    printf("[First Press]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");

    // 3. 버튼 계속 누름
    UpdateLED(&gpioA, &previousButton);
    printf("[Holding]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");

    // 4. 버튼 뗌
    gpioA.IDR &= ~BUTTON_PIN;
    UpdateLED(&gpioA, &previousButton);
    printf("[Released]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");

    // 5. 버튼 다시 누름
    gpioA.IDR |= BUTTON_PIN;
    UpdateLED(&gpioA, &previousButton);
    printf("[Second Press]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");

    // 6. 버튼 다시 뗌
    gpioA.IDR &= ~BUTTON_PIN;
    UpdateLED(&gpioA, &previousButton);
    printf("[Released]\n");
    printf("IDR: 0x%08X\n", (unsigned)gpioA.IDR);
    printf("ODR: 0x%08X\n", (unsigned)gpioA.ODR);
    printf("\n");

    // TODO: 각 단계마다 IDR, ODR 출력

    return 0;
}