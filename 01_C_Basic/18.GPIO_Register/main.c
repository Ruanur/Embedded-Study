#include <stdio.h>
#include <stdint.h>
// #include <stdbool.h>
// #include <string.h>

#define LED_A_PIN (1u << 5) // Bit 5 = 1
#define LED_B_PIN (1u << 6) // Bit 6 = 1

// GPIO_ODR |= LED_A_PIN; -> PIN HIGH
// GPIO_ODR &= ~LED_A_PIN; -> PIN LOW
// GPIO_ODR ^= LED_A_PIN; -> PIN REVERSE (Toggle)

// GPIO PIN HIGH
void GPIO_SetPin(uint32_t *odr, uint32_t pin)
{
    // LED_A_PIN : 32, 00100000
    // LED_B_PIN : 64, 01000000
    *odr |= pin; 

}

// GPIO PIN LOW
void GPIO_ClearPin(uint32_t *odr, uint32_t pin)
{
    *odr &= ~pin;
}

// GPIO PIN STATUS REVERSE
void GPIO_TogglePin(uint32_t *odr, uint32_t pin)
{
    *odr ^= pin;
}

// GPIO PIN STATUS CHECK
int GPIO_ReadPin(uint32_t odr, uint32_t pin)
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
    
    //printf("GPIO_ODR: 0x%08x, switch status: %s\n", (unsigned)odr, status_pin_text);
    return (odr & pin) != 0;
}

int main()
{
    uint32_t GPIO_ODR = 0;
    int statusA = GPIO_ReadPin(GPIO_ODR, LED_A_PIN);
    int statusB = GPIO_ReadPin(GPIO_ODR, LED_B_PIN);

    // TODO: LED A 켜기
    GPIO_SetPin(&GPIO_ODR, LED_A_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(GPIO_ODR, LED_A_PIN);
    statusB = GPIO_ReadPin(GPIO_ODR, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", GPIO_ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    // TODO: LED B 켜기
    GPIO_SetPin(&GPIO_ODR, LED_B_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(GPIO_ODR, LED_A_PIN);
    statusB = GPIO_ReadPin(GPIO_ODR, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", GPIO_ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    // TODO: LED A 끄기
    GPIO_ClearPin(&GPIO_ODR, LED_A_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(GPIO_ODR, LED_A_PIN);
    statusB = GPIO_ReadPin(GPIO_ODR, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", GPIO_ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    // TODO: LED B 토글
    GPIO_TogglePin(&GPIO_ODR, LED_B_PIN);
    // TODO: 레지스터 값 출력
    statusA = GPIO_ReadPin(GPIO_ODR, LED_A_PIN);
    statusB = GPIO_ReadPin(GPIO_ODR, LED_B_PIN);
    printf("GPIO_ODR: 0x%08x\n", GPIO_ODR);
    printf("LED A: %s\n", statusA ? "ON" : "OFF");
    printf("LED B: %s\n", statusB ? "ON" : "OFF");

    return 0;
}