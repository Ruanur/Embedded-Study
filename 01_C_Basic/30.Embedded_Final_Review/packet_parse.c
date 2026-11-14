#include "packet_parse.h"

uint8_t Packet_CalculateChecksum(uint8_t command, uint8_t length, uint8_t data)
{
    // TODO: XOR 체크섬 계산
    return command ^ length ^ data;
}

int Packet_Parse(const uint8_t *raw, size_t size, Packet *packet)
{
    if (raw == NULL || packet == NULL || size != PACKET_SIZE)
    {
        return 0;
    }

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
    case CMD_SENSOR:
        break;
    default:
        return 0;
    }

    // TODO 6: 결과 저장 (command와 data를 packet 구조체에 저장)
    packet->command = raw[1];
    packet->data = raw[3];
    return 1;
}