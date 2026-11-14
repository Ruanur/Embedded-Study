#ifndef PACKET_PARSE_H
#define PACKET_PARSE_H

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
    CMD_RESET = 0x04,
    CMD_SENSOR = 0x05
} Command;

typedef struct
{
    uint8_t command;
    uint8_t data;
} Packet;

uint8_t Packet_CalculateChecksum(uint8_t command, uint8_t length, uint8_t data);

int Packet_Parse(const uint8_t *raw, size_t size, Packet *packet);

#endif