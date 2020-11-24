#ifndef DATABASE_H
#define DATABASE_H
#include <string>

class Frame{
    public:
        struct FrameData{
            uint8_t Byte0;
            uint8_t Byte1;
            uint8_t Byte2;
            uint8_t Byte3;
            uint8_t Byte4;
            uint8_t Byte5;
            uint8_t Byte6;
            uint8_t Byte7;
        };
        uint8_t id = 0;
        FrameData data;
        Frame() = default;
        virtual ~Frame() = default;

        inline void write(class Frame input);
};

inline void Frame::write(class Frame input) {
    data.Byte0 = input.data.Byte0;
    data.Byte1 = input.data.Byte1;
    data.Byte2 = input.data.Byte2;
    data.Byte3 = input.data.Byte3;
    data.Byte4 = input.data.Byte4;
    data.Byte5 = input.data.Byte5;
    data.Byte6 = input.data.Byte6;
    data.Byte7 = input.data.Byte7;
}

//_Inputs______________________________________________________
//____Frame1_Power_ECU_________________________________________
struct Frame1Bitfield { 
    unsigned battery:1;
    unsigned unusedFlag1:1;
    unsigned unusedFlag2:1;
    unsigned unusedFlag3:1;
    unsigned unusedFlag4:1;
    unsigned unusedFlag5:1;
    unsigned unusedFlag6:1;
    unsigned unusedFlag7:1;
};
union Flag1Byte{
        uint8_t byte7 = 0;
        Frame1Bitfield flags;
};
class Frame1 : public Frame {    
    public:
        Frame1() = default;
        ~Frame1() = default;
        struct FrameData{
            uint8_t startBtn = 0; // 0/1 (Off/On)
            uint8_t quitEmul = 0; // 0/1 (KeepRunning/ShutDown)
            uint8_t unusedByte2 =0;
            uint8_t unusedByte3 = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            Flag1Byte flagByte; // Battery
        };
        uint8_t id = 1;
        FrameData data;
        /*inline FrameData read() {
            data.startBtn = Frame::data.Byte0;
            data.quitEmul = Frame::data.Byte1;
            data.unusedByte2 = Frame::data.Byte2;
            data.unusedByte3 = Frame::data.Byte3;
            data.unusedByte4 = Frame::data.Byte4;
            data.unusedByte5 = Frame::data.Byte5;
            data.unusedByte6 = Frame::data.Byte6;
            data.flagByte = Frame::data.Byte7;
            return data;
        }*/
};



//____Frame2_Lights_ECU_________________________________________
struct Frame2Bitfield {
    unsigned hazard:1;
    unsigned right_blinker:1;
    unsigned left_blinker:1;
    unsigned high_beam:1;
    unsigned unusedFlag4:1;
    unsigned unusedFlag5:1;
    unsigned unusedFlag6:1;
    unsigned unusedFlag7:1;
};
union Flag2Byte{
        uint8_t byte7 = 0;
        Frame2Bitfield flags;
};
class Frame2  : public Frame {
    public:
        Frame2() = default;
        ~Frame2() = default;
        struct FrameData {
            uint8_t unusedByte0 = 0;
            uint8_t unusedByte1 = 0;
            uint8_t unusedByte2 = 0;
            uint8_t unusedByte3 = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            Flag2Byte flagByte; // hazard, right_blinker, left_blinker, high_beam
        };
        uint8_t id = 2;
        FrameData data;
};

//____Frame3_Velocity_Manipulation_ECU__________________________
struct Frame3Bitfield {
    unsigned handBrk:1;
    unsigned abs:1;
    unsigned unusedFlag2:1;
    unsigned unusedFlag3:1;
    unsigned unusedFlag4:1;
    unsigned unusedFlag5:1;
    unsigned unusedFlag6:1;
    unsigned unusedFlag7:1;
};
union Flag3Byte{
        uint8_t byte7 = 0;
        Frame3Bitfield flags;
};
class Frame3  : public Frame {
    public:
        Frame3() = default;
        ~Frame3() = default;
        struct FrameData {
            uint8_t brkPdl = 0; //0-100%
            uint8_t accPdl = 0; //0-100%
            uint8_t unusedByte2 = 0;
            uint8_t unusedByte3 = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            Flag3Byte flagByte; // handBrk, abs
        };
        uint8_t id = 3;
        FrameData data;
};

//____Frame4_Rest_of_vehicle___________________________________
struct Frame4Bitfield {
    unsigned seat_belt:1;
    unsigned doors_open:1;
    unsigned unusedFlag2:1;
    unsigned unusedFlag3:1;
    unsigned unusedFlag4:1;
    unsigned unusedFlag5:1;
    unsigned unusedFlag6:1;
    unsigned unusedFlag7:1;
};
union Flag4Byte{
        uint8_t byte7 = 0;
        Frame4Bitfield flags;
};
class Frame4  : public Frame { 
    public:
        Frame4() = default;
        ~Frame4() = default;
        struct FrameData {
            uint8_t gearReq = 0; // 0-4 (P,R,N,D,NoReq)
            uint8_t unusedByte1 = 0;
            uint8_t unusedByte2 = 0;
            uint8_t unusedByte3 = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            Flag4Byte flagByte; // seat_belt, doors_open
        };
        uint8_t id = 4;
        FrameData data;
};

//_Oututs______________________________________________________
//____Frame5_Engine_ECU________________________________________
struct Frame5Bitfield {
    unsigned engine_check:1;
    unsigned oil_check:1;
    unsigned unusedFlag2:1;
    unsigned unusedFlag3:1;
    unsigned unusedFlag4:1;
    unsigned unusedFlag5:1;
    unsigned unusedFlag6:1;
    unsigned unusedFlag7:1;
};
union Flag5Byte{
        uint8_t byte7 = 0;
        Frame5Bitfield flags;
};
class Frame5 : public Frame { 
    public:
        Frame5() = default;
        ~Frame5() = default;
        struct FrameData {
            uint8_t engSts = 0; // 0-450
            uint8_t unusedByte1 = 0;
            uint8_t unusedByte2 = 0;
            uint8_t unusedByte3 = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            Flag5Byte flagByte; // engine_check, oil_check
        };
        uint8_t id = 5;
        FrameData data;
};
//____Frame6_Gearbox_ECU______________________________________
struct Bitfield{
    uint8_t rpmLSB;
    uint8_t rpmMSB; 
};
union RPM{
    uint16_t RPMsignal = 0;
    Bitfield bytes;
};
class Frame6 : public Frame { 
    public:
        Frame6() = default;
        ~Frame6() = default;
        struct FrameData {
            uint8_t gearStick = 0; // 0-3 (P/R/N/D)
            RPM rpm; // uint16_t 0-10000 divided in MSB-LSB
            uint8_t engagedGear = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            uint8_t unusedByte7 = 0;
        };
        uint8_t id = 6;
        FrameData data;
};

#endif