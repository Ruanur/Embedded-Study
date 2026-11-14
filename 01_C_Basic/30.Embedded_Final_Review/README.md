# Day 30 — Embedded Device Simulator

## 1. 프로젝트 개요
C언어를 이용하여 UART 통신 환경을 모의한 장비 제어 시뮬레이터입니다.

## 2. 주요 기능
- Ring Buffer: 수신 데이터를 FIFO 방식으로 관리
- Packet Parser: SOF, LEN, Checksum, Command 검증
- Device FSM: IDLE, RUNNING, ERROR 상태 관리
- Moving Average: 최근 5개 센서 데이터의 이동평균 계산
- Frame Assembler: 수신 바이트를 5바이트 패킷으로 조립

## 3. 프로젝트 구조
- `main.c`: 시뮬레이터 통합 및 실행
- `ring_buffer.h/.c`: 수신 버퍼
- `packet_parse.h/.c`: 패킷 검증
- `device.h/.c`: 장비 상태 머신
- `moving_average.h/.c`: 이동평균 필터
- `tests/test_main.c`: 자동 검증 테스트

## 4. 빌드 방법

시뮬레이터:

```cmd
gcc main.c ring_buffer.c packet_parse.c moving_average.c device.c -o main.exe
main.exe
```

자동 테스트:

```cmd
gcc tests/test_main.c ring_buffer.c packet_parse.c moving_average.c device.c -o tests.exe
tests.exe
```

## 5. 검증 항목
- Ring Buffer FIFO, Full, Empty, Wrap-around
- Packet Parser 정상 및 비정상 패킷
- Device FSM 상태 전환
- Moving Average 계산 및 초기화

## 6. 현재 제한 사항
- 실제 UART 하드웨어 통신은 구현하지 않음
- 손상된 바이트 스트림의 재동기화 기능 미구현
- 테스트는 개별 모듈의 주요 기능을 중심으로 구성
