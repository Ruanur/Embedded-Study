#include <stdio.h>
#include <stdint.h>

#define GPIO_MODE_INPUT 0u
#define GPIO_MODE_OUTPUT 1u

#define LED_A_PIN_NUMBER 5u
#define LED_B_PIN_NUMBER 6u

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
    uint32_t shift = pinNumber * 2; // 10 
    uint32_t mask = 3u << shift; // 00 00 11 00 00 00 00 00 
    // 2. 기존 2비트 삭제
    gpio->MODER &= ~mask;
    // 3. 새로운 모드 설정
    gpio->MODER |= (mode << shift);
}

int GPIO_GetMode(const volatile GPIO_Registers *gpio, uint32_t pinNumber)
{
    // TODO 
    // 해당 핀의 모드 2비트만 추출

    uint32_t shift = pinNumber * 2;
    return (gpio->MODER >> shift) & 0x03;
}

int main(void)
{
    volatile GPIO_Registers gpioA = {0};

    // TODO: Pin 5 -> Output
    // TODO: MODER 출력
    GPIO_SetMode(&gpioA, 5, GPIO_MODE_OUTPUT);
    printf("MODER: 0x%08X\n", (unsigned)gpioA.MODER);
    // TODO: Pin 6 -> Output
    // TODO: MODER 출력
    GPIO_SetMode(&gpioA, 6, GPIO_MODE_OUTPUT);
    printf("MODER: 0x%08X\n", (unsigned)gpioA.MODER);
    // TODO: Pin 5, Pin 6 모드 확인
    printf("Pin 5 Mode: %u\n",(unsigned)GPIO_GetMode(&gpioA, LED_A_PIN_NUMBER));
    printf("Pin 6 Mode: %u\n", (unsigned)GPIO_GetMode(&gpioA, LED_B_PIN_NUMBER));
    // TODO: Pin 5 -> Input
    GPIO_SetMode(&gpioA, 5, GPIO_MODE_INPUT);
    // TODO: MODER 출력
    printf("MODER: 0x%08X\n", (unsigned)gpioA.MODER);
    return 0;
}