#include "device.h"

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