
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#define RX_BUFFER_SIZE 32u
#define PACKET_SOF 0xAAu
#define PACKET_SIZE 5u
#define PAYLOAD_LEN 1u
#define WINDOW_SIZE 5u

typedef enum
{
    CMD_START = 1,
    CMD_STOP,
    CMD_FAULT,
    CMD_RESET,
    CMD_SENSOR
} Command;

typedef enum
{
    DEVICE_IDLE,
    DEVICE_RUNNING,
    DEVICE_ERROR
} DeviceState;

typedef enum
{
    EVENT_START,
    EVENT_STOP,
    EVENT_FAULT,
    EVENT_RESET
} DeviceEvent;

typedef struct
{
    uint8_t data[RX_BUFFER_SIZE];
    size_t head, tail, count;
} RingBuffer;

typedef struct
{
    uint8_t command;
    uint8_t data;
} Packet;

typedef struct
{
    DeviceState state;
} Device;

typedef struct
{
    uint16_t data[WINDOW_SIZE];
    size_t head, count;
    uint32_t sum;
} MovingAverage;

typedef struct
{
    uint8_t frame[PACKET_SIZE];
    size_t received;
} FrameAssembler;

/* Day 25: Ring Buffer */

void RingBuffer_Init(RingBuffer *rb)
{
    rb->head = rb->tail = rb->count = 0;
}

int RingBuffer_Enqueue(RingBuffer *rb, uint8_t value)
{
    if (rb->count == RX_BUFFER_SIZE)
        return 0;

    rb->data[rb->head] = value;
    rb->head = (rb->head + 1) % RX_BUFFER_SIZE;
    rb->count++;
    return 1;
}

int RingBuffer_Dequeue(RingBuffer *rb, uint8_t *value)
{
    if (rb->count == 0)
        return 0;

    *value = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % RX_BUFFER_SIZE;
    rb->count--;
    return 1;
}

/* Day 26: Device FSM */

void Device_Init(Device *device)
{
    device->state = DEVICE_IDLE;
}

void Device_ProcessEvent(Device *device, DeviceEvent event)
{
    switch (device->state)
    {
    case DEVICE_IDLE:
        if (event == EVENT_START)
            device->state = DEVICE_RUNNING;
        else if (event == EVENT_FAULT)
            device->state = DEVICE_ERROR;
        break;

    case DEVICE_RUNNING:
        if (event == EVENT_STOP)
            device->state = DEVICE_IDLE;
        else if (event == EVENT_FAULT)
            device->state = DEVICE_ERROR;
        break;

    case DEVICE_ERROR:
        if (event == EVENT_RESET)
            device->state = DEVICE_IDLE;
        break;

    default:
        break;
    }
}

const char *Device_StateName(DeviceState state)
{
    switch (state)
    {
    case DEVICE_IDLE:
        return "IDLE";
    case DEVICE_RUNNING:
        return "RUNNING";
    case DEVICE_ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

/* Day 27: Packet Parser */

uint8_t Packet_CalculateChecksum(
    uint8_t command, uint8_t length, uint8_t data)
{
    return (uint8_t)(command ^ length ^ data);
}

int Packet_Parse(const uint8_t *raw, size_t size, Packet *packet)
{
    if (raw == NULL || packet == NULL || size != PACKET_SIZE)
        return 0;

    if (raw[0] != PACKET_SOF || raw[2] != PAYLOAD_LEN)
        return 0;

    if (Packet_CalculateChecksum(raw[1], raw[2], raw[3]) != raw[4])
        return 0;

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

    packet->command = raw[1];
    packet->data = raw[3];
    return 1;
}

/* Day 28: Moving Average */

void MovingAverage_Init(MovingAverage *filter)
{
    filter->head = 0;
    filter->count = 0;
    filter->sum = 0;
}

void MovingAverage_Add(MovingAverage *filter, uint16_t value)
{
    if (filter->count < WINDOW_SIZE)
    {
        filter->sum += value;
        filter->count++;
    }
    else
    {
        filter->sum -= filter->data[filter->head];
        filter->sum += value;
    }

    filter->data[filter->head] = value;
    filter->head = (filter->head + 1) % WINDOW_SIZE;
}

double MovingAverage_Get(const MovingAverage *filter)
{
    if (filter->count == 0)
        return 0.0;

    return (double)filter->sum / filter->count;
}

/* Day 29: Integration — 직접 구현할 부분 */

void Device_HandlePacket(
    Device *device,
    MovingAverage *filter,
    const Packet *packet)
{
    if (packet->command == CMD_SENSOR)
    {
        // TODO 1:
        // RUNNING이면 MovingAverage_Add() 호출
        if (device->state == DEVICE_RUNNING)
        {
            MovingAverage_Add(filter, packet->data);

            // 평균과 count 출력
            printf("[SENSOR] Input: %u | Average: %.2f | Count: %zu\n",
                   (unsigned)packet->data,
                   MovingAverage_Get(filter),
                   filter->count);
            
        }
        else
        {
            // RUNNING이 아니면 센서 데이터 무시
            printf("[SENSOR] Ignored (%s)\n",
                   Device_StateName(device->state));
            return;
        }
        return;
    }
    DeviceState before = device->state;

    // TODO 2:
    // Device_ProcessEvent() 호출
    switch (packet->command)
    {
    // CMD_START -> EVENT_START
    case CMD_START:
        Device_ProcessEvent(device, EVENT_START);
        break;
    // CMD_STOP  -> EVENT_STOP
    case CMD_STOP:
        Device_ProcessEvent(device, EVENT_STOP);
        break;
    // CMD_FAULT -> EVENT_FAULT
    case CMD_FAULT:
        Device_ProcessEvent(device, EVENT_FAULT);
        break;
    // CMD_RESET -> EVENT_RESET
    case CMD_RESET:
        Device_ProcessEvent(device, EVENT_RESET);
        break;

    default:
        break;
    }

    // TODO 3:
    // ERROR에서 RESET으로 IDLE이 되었다면
    // MovingAverage_Init() 호출
    if (before == DEVICE_ERROR && device->state == DEVICE_IDLE)
    {
        MovingAverage_Init(filter);
    }

    printf("[CMD %02X] %s -> %s\n",
           (unsigned)packet->command,
           Device_StateName(before),
           Device_StateName(device->state));

    (void)filter;
}

void FrameAssembler_Input(
    FrameAssembler *assembler,
    uint8_t byte,
    Device *device,
    MovingAverage *filter)
{
    // TODO 4:
    // received == 0이고 byte가 SOF가 아니면 무시
    if (assembler->received == 0 && byte != PACKET_SOF)
    {
        return;
    }

    // TODO 5:
    // frame[received]에 byte 저장
    // received 증가
    assembler->frame[assembler->received] = byte;
    assembler->received++;

    // TODO 6:
    // PACKET_SIZE만큼 모이지 않았다면 return
    if (assembler->received < 5)
    {
        return;
    }

    // TODO 7:
    // 5바이트가 모이면 received를 0으로 초기화
    // Packet_Parse() 호출
    Packet parsed = {0};

    int result = Packet_Parse(assembler->frame, PACKET_SIZE, &parsed);
    assembler->received = 0;

    if (result == 1)
    {
        Device_HandlePacket(device, filter, &parsed);
    }
    else
    {
        printf("[RX] Invalid Packet\n");
    }
    // 성공 -> Device_HandlePacket()
    // 실패 -> "[RX] Invalid Packet" 출력
}

/* 수신 버퍼에 쌓인 바이트 처리 */

void ProcessRx(
    RingBuffer *rx,
    FrameAssembler *assembler,
    Device *device,
    MovingAverage *filter)
{
    uint8_t byte;

    while (RingBuffer_Dequeue(rx, &byte))
    {
        FrameAssembler_Input(assembler, byte, device, filter);
    }
}

int main(void)
{
    RingBuffer rx;
    Device device;
    MovingAverage filter;
    FrameAssembler assembler = {0};

    RingBuffer_Init(&rx);
    Device_Init(&device);
    MovingAverage_Init(&filter);

    /* cmd, data, checksum을 일부러 손상시킬지 여부 */
    const struct
    {
        uint8_t command;
        uint8_t data;
        int badChecksum;
    } tests[] = {
        {CMD_START, 0, 0},
        {CMD_SENSOR, 20, 0},
        {CMD_SENSOR, 22, 0},
        {CMD_SENSOR, 21, 0},
        {CMD_SENSOR, 80, 0},
        {CMD_SENSOR, 23, 0},
        {CMD_SENSOR, 24, 0},
        {CMD_SENSOR, 25, 0},
        {CMD_STOP, 0, 0},
        {CMD_SENSOR, 40, 0},
        {CMD_START, 0, 0},
        {CMD_FAULT, 0, 0},
        {CMD_SENSOR, 90, 0},
        {CMD_START, 0, 0},
        {CMD_RESET, 0, 0},
        {CMD_START, 0, 0},
        {CMD_SENSOR, 30, 0},
        {CMD_SENSOR, 31, 1},
        {0x09, 0, 0}
    };

    size_t byteCount = 0;

    printf("Initial State: %s\n",
           Device_StateName(device.state));

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        uint8_t frame[PACKET_SIZE] = {
            PACKET_SOF,
            tests[i].command,
            PAYLOAD_LEN,
            tests[i].data,
            Packet_CalculateChecksum(
                tests[i].command, PAYLOAD_LEN, tests[i].data)};

        if (tests[i].badChecksum)
            frame[4] ^= 0xFFu;

        for (size_t j = 0; j < PACKET_SIZE; j++)
        {
            if (!RingBuffer_Enqueue(&rx, frame[j]))
            {
                printf("[RX] Buffer Full!\n");
            }

            byteCount++;

            // UART 데이터가 일정하지 않은 크기로
            // 처리되는 상황을 가정
            if (byteCount % 7u == 0u)
            {
                ProcessRx(&rx, &assembler, &device, &filter);
            }
        }
    }

    // 마지막에 남은 바이트 처리
    ProcessRx(&rx, &assembler, &device, &filter);

    return 0;
}
