#ifndef CANIO_H
#define CANIO_H
#include <iostream>
#include "socketcan_cpp.h"
#include "../../SharedMemory/Include/shared_memory.h"

struct bitpattern1 {
        unsigned hazard:1;
        unsigned right_blinker:1;
        unsigned left_blinker:1;
        unsigned engine_check:1;
        unsigned oil_check:1;
        unsigned abs:1;
        unsigned battery:1;
        unsigned seat_belt:1;
};

struct bitpattern2 {
        unsigned doors_open:1;
        unsigned high_beam:1;
        unsigned hand_break:1;
};
union telltales1 {
    uint8_t canByte;
    bitpattern1 telltales1;
};
union telltales2 {
    uint8_t canByte;;
    bitpattern2 telltales2;
};

struct CanInput
{
    int8_t brkPdl;
    int8_t accPdl;
    int8_t gearReq;
    int8_t startBtn;
    int8_t quitEmul;
    telltales1 ttByte1;
    telltales2 ttByte2;

    CanInput() {brkPdl=0; accPdl=0; gearReq=0; startBtn=0; quitEmul=0;}

    void write(CanInput input);
};

struct CanOutput
{
    uint8_t vhlSpeed;
    uint8_t gearStick;
    uint16_t RPM;
    uint8_t engagedGear;
    CanOutput() {vhlSpeed=2; gearStick=0; RPM=0; engagedGear=0;}

    void write(CanOutput output);
};

class CANIO{
public:
    CANIO() = default;
    ~CANIO() = default;
    scpp::SocketCan sockat_can;
    CanInput canIn; // persistent object needed for readCANWriteToMemory
    bool start_can();
    bool readCANWriteToMemory(SharedMemory<CanInput> *CanInput);
    void frameToBus(uint8_t frameNo, uint8_t signalValue);
    void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint8_t signal2Value);
    void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value, uint8_t signal3Value);
};
#endif
