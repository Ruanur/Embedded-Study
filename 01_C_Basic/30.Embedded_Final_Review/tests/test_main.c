
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>

#include "../ring_buffer.h"
#include "../packet_parse.h"
#include "../moving_average.h"
#include "../device.h"

// =====================================
// 1. Ring Buffer 기본 테스트
// =====================================
void Test_RingBuffer(void)
{
    RingBuffer rb;
    uint8_t value = 0;

    RingBuffer_Init(&rb);

    // 1. 초기 상태 확인
    assert(rb.count == 0);

    // 2. 데이터 저장
    assert(RingBuffer_Enqueue(&rb, 10) == 1);
    assert(RingBuffer_Enqueue(&rb, 20) == 1);
    assert(RingBuffer_Enqueue(&rb, 30) == 1);

    // 3. FIFO 순서 확인
    assert(RingBuffer_Dequeue(&rb, &value) == 1);
    assert(value == 10);

    // TODO 1: 다음 데이터 20이 나오는지 검사
    assert(RingBuffer_Dequeue(&rb, &value) == 1);
    assert(value == 20);

    // TODO 2: 다음 데이터 30이 나오는지 검사
    assert(RingBuffer_Dequeue(&rb, &value) == 1);
    assert(value == 30);

    // TODO 3: 버퍼가 비었을 때 Dequeue가
    assert(RingBuffer_Dequeue(&rb, &value) == 0);
    // 실패하는지 검사

    printf("[PASS] Ring Buffer\n");
}

// =====================================
// 2. Ring Buffer Full 테스트
// =====================================
void Test_RingBufferFull(void)
{
    RingBuffer rb;
    RingBuffer_Init(&rb);

    // TODO 1: for문을 이용해 32개 데이터 저장
    // 모든 Enqueue가 1을 반환하는지 확인
    for (size_t i = 0; i < RX_BUFFER_SIZE; i++)
    {
        assert(RingBuffer_Enqueue(&rb, (uint8_t)i) == 1);
    }

    // TODO 2: rb.count == RX_BUFFER_SIZE 확인
    assert(rb.count == RX_BUFFER_SIZE);

    // TODO 3: 33번째 데이터를 저장하고
    // 반환값이 0인지 확인
    assert(RingBuffer_Enqueue(&rb, 100) == 0);

    // TODO 4: 저장 실패 후에도
    // rb.count == RX_BUFFER_SIZE인지 확인
    assert(rb.count == RX_BUFFER_SIZE);

    uint8_t value = 0;

    for (size_t i = 0; i < RX_BUFFER_SIZE; i++)
    {
        assert(RingBuffer_Dequeue(&rb, &value) == 1);
        assert(value == (uint8_t)i);
    }

    assert(rb.count == 0);
    assert(RingBuffer_Dequeue(&rb, &value) == 0);

    printf("[PASS] Ring Buffer Full\n");
}

// =====================================
// 3. Ring Buffer Wrap-around 테스트
// =====================================
void Test_RingBufferWrapAround(void)
{
    RingBuffer rb;
    uint8_t value = 0;

    RingBuffer_Init(&rb);

    // 32개 데이터 저장: 0 ~ 31
    for (size_t i = 0; i < RX_BUFFER_SIZE; i++)
    {
        assert(
            RingBuffer_Enqueue(&rb, (uint8_t)i) == 1);
    }

    assert(rb.head == 0);

    // 앞의 10개 데이터 제거
    for (size_t i = 0; i < 10; i++)
    {
        assert(RingBuffer_Dequeue(&rb, &value) == 1);
        assert(value == (uint8_t)i);
    }

    assert(rb.count == RX_BUFFER_SIZE - 10);
    assert(rb.tail == 10);

    // 새로운 데이터 32 ~ 41 저장
    for (size_t i = 0; i < 10; i++)
    {
        assert(
            RingBuffer_Enqueue(
                &rb, (uint8_t)(RX_BUFFER_SIZE + i)) == 1);
    }

    // head가 0부터 다시 이동했는지 확인
    assert(rb.head == 10);
    assert(rb.count == RX_BUFFER_SIZE);

    // 남은 데이터 10 ~ 41 검증
    for (size_t i = 10; i < RX_BUFFER_SIZE + 10; i++)
    {
        assert(RingBuffer_Dequeue(&rb, &value) == 1);
        assert(value == (uint8_t)i);
    }

    assert(rb.count == 0);
    assert(rb.tail == rb.head);

    printf("[PASS] Ring Buffer Wrap-around\n");
}

// =====================================
// 4. Packet Parser 테스트
// =====================================
void Test_PacketParser(void)
{
    Packet packet = {0};

    // 정상 START 패킷
    uint8_t raw[PACKET_SIZE] = {
        PACKET_SOF,
        CMD_START,
        PAYLOAD_LEN,
        0x12,
        0};

    raw[4] = Packet_CalculateChecksum(
        raw[1], raw[2], raw[3]);

    // 정상 패킷 파싱
    assert(Packet_Parse(raw, PACKET_SIZE, &packet) == 1);
    assert(packet.command == CMD_START);
    assert(packet.data == 0x12);

    // 정상 SENSOR 패킷
    raw[1] = CMD_SENSOR;
    raw[3] = 25;
    raw[4] = Packet_CalculateChecksum(
        raw[1], raw[2], raw[3]);

    assert(Packet_Parse(raw, PACKET_SIZE, &packet) == 1);
    assert(packet.command == CMD_SENSOR);
    assert(packet.data == 25);

    // 잘못된 크기
    assert(Packet_Parse(raw, 4, &packet) == 0);
    assert(Packet_Parse(raw, 6, &packet) == 0);

    // 잘못된 SOF
    raw[0] = 0xBB;
    assert(Packet_Parse(raw, PACKET_SIZE, &packet) == 0);
    raw[0] = PACKET_SOF;

    // 잘못된 LEN
    raw[2] = 2;
    assert(Packet_Parse(raw, PACKET_SIZE, &packet) == 0);
    raw[2] = PAYLOAD_LEN;

    // 잘못된 체크섬
    raw[4] ^= 0xFFu;
    assert(Packet_Parse(raw, PACKET_SIZE, &packet) == 0);
    raw[4] ^= 0xFFu;

    // 유효하지 않은 명령어
    raw[1] = 0x09;
    raw[4] = Packet_CalculateChecksum(
        raw[1], raw[2], raw[3]);

    assert(Packet_Parse(raw, PACKET_SIZE, &packet) == 0);

    // NULL 포인터 검사
    assert(Packet_Parse(NULL, PACKET_SIZE, &packet) == 0);
    assert(Packet_Parse(raw, PACKET_SIZE, NULL) == 0);

    printf("[PASS] Packet Parser\n");
}

// =====================================
// 5. Device FSM 테스트
// =====================================
void Test_Device(void)
{
    Device device;

    Device_Init(&device);

    // 초기 상태
    assert(device.state == DEVICE_IDLE);

    // IDLE에서 STOP은 무시
    Device_ProcessEvent(&device, EVENT_STOP);
    assert(device.state == DEVICE_IDLE);

    // IDLE -> RUNNING
    Device_ProcessEvent(&device, EVENT_START);
    assert(device.state == DEVICE_RUNNING);

    // RUNNING에서 START는 무시
    Device_ProcessEvent(&device, EVENT_START);
    assert(device.state == DEVICE_RUNNING);

    // RUNNING -> IDLE
    Device_ProcessEvent(&device, EVENT_STOP);
    assert(device.state == DEVICE_IDLE);

    // IDLE -> RUNNING
    Device_ProcessEvent(&device, EVENT_START);
    assert(device.state == DEVICE_RUNNING);

    // RUNNING -> ERROR
    Device_ProcessEvent(&device, EVENT_FAULT);
    assert(device.state == DEVICE_ERROR);

    // ERROR에서 START는 무시
    Device_ProcessEvent(&device, EVENT_START);
    assert(device.state == DEVICE_ERROR);

    // ERROR에서 STOP도 무시
    Device_ProcessEvent(&device, EVENT_STOP);
    assert(device.state == DEVICE_ERROR);

    // ERROR -> IDLE
    Device_ProcessEvent(&device, EVENT_RESET);
    assert(device.state == DEVICE_IDLE);

    // IDLE에서 직접 FAULT
    Device_ProcessEvent(&device, EVENT_FAULT);
    assert(device.state == DEVICE_ERROR);

    // 다시 복구
    Device_ProcessEvent(&device, EVENT_RESET);
    assert(device.state == DEVICE_IDLE);

    // 상태 이름 검사
    assert(strcmp(Device_StateName(DEVICE_IDLE), "IDLE") == 0);

    assert(strcmp(Device_StateName(DEVICE_RUNNING), "RUNNING") == 0);

    assert(strcmp(Device_StateName(DEVICE_ERROR), "ERROR") == 0);

    printf("[PASS] Device FSM\n");
}

// =====================================
// 6. Moving Average 테스트
// =====================================

// 부동소수점 오차를 고려한 평균 비교
void Assert_AverageNear(double actual, double expected)
{
    double difference = actual - expected;

    assert(difference > -0.000001);
    assert(difference < 0.000001);
}

void Test_MovingAverage(void)
{
    MovingAverage filter;

    MovingAverage_Init(&filter);

    // 초기 상태
    assert(filter.count == 0);
    assert(filter.head == 0);
    assert(filter.sum == 0);
    Assert_AverageNear(MovingAverage_Get(&filter), 0.0);

    // 20
    MovingAverage_Add(&filter, 20);
    assert(filter.count == 1);
    Assert_AverageNear(MovingAverage_Get(&filter), 20.0);

    // 20, 22
    MovingAverage_Add(&filter, 22);
    assert(filter.count == 2);
    Assert_AverageNear(MovingAverage_Get(&filter), 21.0);

    // 20, 22, 21
    MovingAverage_Add(&filter, 21);
    Assert_AverageNear(MovingAverage_Get(&filter), 21.0);

    // 20, 22, 21, 80
    MovingAverage_Add(&filter, 80);
    Assert_AverageNear(MovingAverage_Get(&filter), 35.75);

    // 20, 22, 21, 80, 23
    MovingAverage_Add(&filter, 23);
    assert(filter.count == WINDOW_SIZE);
    assert(filter.sum == 166);
    Assert_AverageNear(MovingAverage_Get(&filter), 33.2);

    // 오래된 20 제거, 새로운 24 추가
    MovingAverage_Add(&filter, 24);
    assert(filter.count == WINDOW_SIZE);
    assert(filter.sum == 170);
    Assert_AverageNear(MovingAverage_Get(&filter), 34.0);

    // 오래된 22 제거, 새로운 25 추가
    MovingAverage_Add(&filter, 25);
    assert(filter.count == WINDOW_SIZE);
    assert(filter.sum == 173);
    Assert_AverageNear(MovingAverage_Get(&filter), 34.6);

    // 재초기화
    MovingAverage_Init(&filter);

    assert(filter.count == 0);
    assert(filter.head == 0);
    assert(filter.sum == 0);
    Assert_AverageNear(MovingAverage_Get(&filter), 0.0);

    // 초기화 이후 새로운 값
    MovingAverage_Add(&filter, 30);
    assert(filter.count == 1);
    Assert_AverageNear(MovingAverage_Get(&filter), 30.0);

    printf("[PASS] Moving Average\n");
}

// =====================================
// 전체 테스트 실행
// =====================================
int main(void)
{
    Test_RingBuffer();
    Test_RingBufferFull();
    Test_RingBufferWrapAround();

    Test_PacketParser();
    Test_Device();
    Test_MovingAverage();

    printf("All tests passed!\n");
    return 0;
}
