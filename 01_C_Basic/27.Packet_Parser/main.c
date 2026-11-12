#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define PACKET_SOF 0xAAu
#define PACKET_SIZE 5u
#define PAYLOAD_LEN 1u

typedef enum
{
    CMD_START = 0x01,
    CMD_STOP = 0x02,
    CMD_FAULT = 0x03,
    CMD_RESET = 0x04
} Command;

typedef struct
{
    uint8_t command;
    uint8_t data;
} Packet;

uint8_t Packet_CalculateChecksum(
    uint8_t command,
    uint8_t length,
    uint8_t data)
{
    // TODO: XOR 체크섬 계산
    return command ^ length ^ data;
}

int Packet_Parse(
    const uint8_t *raw,
    size_t size,
    Packet *packet)
{
    // TODO 1: 크기 검사 (패킷 크기가 5바이트인가?)
    if (PACKET_SIZE != size)
    {
        return 0;
    }

    // TODO 2: SOF 검사 (0xAA인가?)

    if (PACKET_SOF != raw[0])
    {
        return 0;
    }

    // TODO 3: LEN 검사 (LEN이 1인가?)
    if (PAYLOAD_LEN != raw[2])
    {
        return 0;
    }

    // TODO 4: 체크섬 검사 (계산 및 비교)
    uint8_t calculatedCHK = Packet_CalculateChecksum(raw[1], raw[2], raw[3]);
    if (calculatedCHK != raw[4])
    {
        return 0;
    }

    // TODO 5: 명령어 유효성 검사 (명령어가 START, STOP, FAULT, RESET 중 하나인지)
    switch (raw[1])
    {
        case CMD_START:
        case CMD_STOP:
        case CMD_FAULT:
        case CMD_RESET:
            break;
        default:
            return 0;
    }

    // TODO 6: 결과 저장 (command와 data를 packet 구조체에 저장)
    packet->command = raw[1];
    packet->data = raw[3];
    return 1;
}

int main(void)
{
    // SOF CMD LEN DATA CHK

    uint8_t startPacket[PACKET_SIZE] =
        {0xAA, 0x01, 0x01, 0x00, 0x00};

    uint8_t stopPacket[PACKET_SIZE] =
        {0xAA, 0x02, 0x01, 0x00, 0x03};

    uint8_t errorPacket[PACKET_SIZE] =
        {0xAA, 0x01, 0x01, 0x00, 0xFF};

    uint8_t invalidSofPacket[PACKET_SIZE] =
        {0xAB, 0x01, 0x01, 0x00, 0x00};

    Packet packet = {0};

    // TODO 1: START 패킷 파싱
    int result = Packet_Parse(startPacket, sizeof(startPacket), &packet);

    printf("[START Packet]\n");
    if (result == 1)
    {
        printf("Valid Packet!\n");
        printf("Command: 0x%02X\n", (unsigned)packet.command);
        printf("Data: 0x%02X\n", (unsigned)packet.data);
    }
    else
    {
        printf("Invalid Packet!\n");
    }
    printf("\n");

    // TODO 2: STOP 패킷 파싱
    result = Packet_Parse(stopPacket, sizeof(stopPacket), &packet);

    printf("[STOP Packet]\n");
    if (result == 1)
    {
        printf("Valid Packet!\n");
        printf("Command: 0x%02X\n", (unsigned)packet.command);
        printf("Data: 0x%02X\n", (unsigned)packet.data);
    }
    else
    {
        printf("Invalid Packet!\n");
    }
    printf("\n");

    // TODO 3: 체크섬 오류 패킷 파싱
    printf("[CHECKSUM Error]\n");
    result = Packet_Parse(errorPacket, sizeof(errorPacket), &packet);
    if (result == 0)
    {
        printf("Invalid Packet\n");
    }
    printf("\n");

    // TODO 4: 시작 바이트 오류 패킷 파싱
    printf("[SOF Error]\n");
    result = Packet_Parse(invalidSofPacket, sizeof(invalidSofPacket), &packet);
    if (result == 0)
    {
        printf("Invalid Packet\n");
    }
    printf("\n");

    // TODO 5: 각각 성공 또는 실패 출력
    

    return 0;
}