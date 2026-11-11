#include <stdio.h>
#include <stddef.h>

typedef enum
{
    DEVICE_IDLE, // 장비 대기 상태
    DEVICE_RUNNING, // 장비 정상 작동
    DEVICE_ERROR // 오류 발생, 정상 작동 불가
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
    DeviceState state;
} Device;

typedef struct
{
    DeviceEvent event;
    const char *name;
} TestCase;

void Device_Init(Device *device)
{
    // TODO: 초기 상태 설정
    device->state = DEVICE_IDLE;
}

void Device_ProcessEvent(Device *device, DeviceEvent event)
{
    // TODO: 현재 상태별 이벤트 처리

    switch (device->state)
    {
    case DEVICE_IDLE:
        if (event == EVENT_FAULT)
        {
            // TODO: FAULT → ERROR
            device->state = DEVICE_ERROR;
        }
        else if (event == EVENT_START)
        {
            // TODO: START → RUNNING
            device->state = DEVICE_RUNNING;
        }
        break;

    case DEVICE_RUNNING:
        if (event == EVENT_FAULT)
        {
            // TODO: FAULT → ERROR
            device->state = DEVICE_ERROR;
        }
        else if (event == EVENT_STOP)
        {
            // TODO: STOP → IDLE
            device->state = DEVICE_IDLE;
        }
        break;

    case DEVICE_ERROR:
        // TODO: RESET → IDLE
        if (event == EVENT_RESET)
        {
            device->state = DEVICE_IDLE;
        }
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

int main(void)
{
    Device device;
    Device_Init(&device);

    TestCase tests[] =
        {
            {EVENT_START, "START"},
            {EVENT_START, "START"},
            {EVENT_FAULT, "FAULT"},
            {EVENT_START, "START"},
            {EVENT_STOP, "STOP"},
            {EVENT_RESET, "RESET"},
            {EVENT_STOP, "STOP"},
            {EVENT_FAULT, "FAULT"},
            {EVENT_RESET, "RESET"},
            {EVENT_START, "START"},
            {EVENT_STOP, "STOP"}
        };

    size_t count = sizeof(tests) / sizeof(tests[0]);

    printf("Initial State: %s\n",
           Device_StateName(device.state));

    for (size_t i = 0; i < count; i++)
    {
        Device_ProcessEvent(&device, tests[i].event);

        printf("[%-5s] State: %s\n",
               tests[i].name,
               Device_StateName(device.state));
    }

    return 0;
}