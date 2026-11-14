#ifndef DEVICE_H
#define DEVICE_H

#include <stddef.h>

typedef enum
{
    DEVICE_IDLE,    // 장비 대기 상태
    DEVICE_RUNNING, // 장비 정상 작동
    DEVICE_ERROR    // 오류 발생, 정상 작동 불가
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

void Device_Init(Device *device);

void Device_ProcessEvent(Device *device, DeviceEvent event);

const char *Device_StateName(DeviceState state);

#endif