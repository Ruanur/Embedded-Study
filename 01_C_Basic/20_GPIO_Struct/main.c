#include <stdio.h>
#include <stdint.h>

#define LED_A_PIN (1u << 5) // Bit 5 = 1
#define LED_B_PIN (1u << 6) // Bit 6 = 1

typedef struct 
{
    /* data */
    uint32_t MODER;
    uint32_t IDR;
    uint32_t ODR;

} GPIO_Registers;


// GPIO_ODR |= LED_A_PIN; -> PIN HIGH
// GPIO_ODR &= ~LED_A_PIN; -> PIN LOW
// GPIO_ODR ^= LED_A_PIN; -> PIN REVERSE (Toggle)

// GPIO PIN HIGH
void GPIO_SetPin(volatile GPIO_Registers *gpio, uint32_t pin)
{
    gpio->ODR |= pin;
}

// GPIO PIN LOW
void GPIO_ClearPin(volatile GPIO_Registers *gpio, uint32_t pin)
{
    gpio->ODR &= ~pin;
}

// GPIO PIN STATUS REVERSE
void GPIO_TogglePin(volatile GPIO_Registers *gpio, uint32_t pin)
{
    gpio->ODR ^= pin;
}

// GPIO PIN STATUS CHECK
int GPIO_ReadPin(const volatile GPIO_Registers *gpio, uint32_t pin)
{
    // bool status_pin = odr & pin;
    // char status_pin_text[4] = "off";

    // if (status_pin == 1)
    // {
    //     strcpy(status_pin_text, "on");
    // }
    // else
    // {
    //     strcpy(status_pin_text, "off");
    // }

    // printf("GPIO_ODR: 0x%08x, switch status: %s\n", (unsigned)odr, status_pin_text);
    return (gpio->ODR & pin) != 0;
}

int main()
{
    volatile GPIO_Registers gpioA = {0};
    int statusA;
    int statusB;

    // TODO: LED A 켜기
    GPIO_SetPin(&gpioA, LED_A_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(&gpioA, LED_A_PIN);
    statusB = GPIO_ReadPin(&gpioA, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", (unsigned)gpioA.ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    // TODO: LED B 켜기
    GPIO_SetPin(&gpioA, LED_B_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(&gpioA, LED_A_PIN);
    statusB = GPIO_ReadPin(&gpioA, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", (unsigned)gpioA.ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    // TODO: LED A 끄기
    GPIO_ClearPin(&gpioA, LED_A_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(&gpioA, LED_A_PIN);
    statusB = GPIO_ReadPin(&gpioA, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", (unsigned)gpioA.ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    // TODO: LED B 토글
    GPIO_TogglePin(&gpioA, LED_B_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(&gpioA, LED_A_PIN);
    statusB = GPIO_ReadPin(&gpioA, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", (unsigned)gpioA.ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    return 0;
}