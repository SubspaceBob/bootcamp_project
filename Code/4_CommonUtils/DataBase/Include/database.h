#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>

class Frame{
    public:
        Frame() = default;
        ~Frame() = default;

        uint32_t id;
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
        FrameData data;     

        virtual void write() {}
};

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
        Frame1() {this->id = 1;}
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
        FrameData data;

        inline void write();
};

inline void Frame1::write() {
    Frame::data.Byte0 = data.startBtn;
    Frame::data.Byte1 = data.quitEmul;
    Frame::data.Byte2 = data.unusedByte2;
    Frame::data.Byte3 = data.unusedByte3;
    Frame::data.Byte4 = data.unusedByte4;
    Frame::data.Byte5 = data.unusedByte5;
    Frame::data.Byte6 = data.unusedByte6;
    Frame::data.Byte7 = data.flagByte.byte7;
}

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
class Frame2 : public Frame {
    public:
        Frame2() {this->id = 2;}
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
        FrameData data;

        inline void write();
};

inline void Frame2::write() {
    Frame::data.Byte0 = data.unusedByte0;
    Frame::data.Byte1 = data.unusedByte1;
    Frame::data.Byte2 = data.unusedByte2;
    Frame::data.Byte3 = data.unusedByte3;
    Frame::data.Byte4 = data.unusedByte4;
    Frame::data.Byte5 = data.unusedByte5;
    Frame::data.Byte6 = data.unusedByte6;
    Frame::data.Byte7 = data.flagByte.byte7;
}


//____Frame3_Velocity_Manipulation_ECU__________________________
struct Frame3Bitfield {
    unsigned hand_brake:1;
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
class Frame3 : public Frame {
    public:
        Frame3() {this->id = 3;}
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
        FrameData data;

        inline void write();
};

inline void Frame3::write() {
    Frame::data.Byte0 = data.brkPdl;
    Frame::data.Byte1 = data.accPdl;
    Frame::data.Byte2 = data.unusedByte2;
    Frame::data.Byte3 = data.unusedByte3;
    Frame::data.Byte4 = data.unusedByte4;
    Frame::data.Byte5 = data.unusedByte5;
    Frame::data.Byte6 = data.unusedByte6;
    Frame::data.Byte7 = data.flagByte.byte7;
}

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
class Frame4 : public Frame { 
    public:
        Frame4() {this->id = 4;}
        ~Frame4() = default;

        struct FrameData {
            uint8_t gearReq = 0; // 0-4 (P, R, N, D, NoReq)
            uint8_t unusedByte1 = 0;
            uint8_t unusedByte2 = 0;
            uint8_t unusedByte3 = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            Flag4Byte flagByte; // seat_belt, doors_open
        };
        FrameData data;

        inline void write();
};

inline void Frame4::write() {
    Frame::data.Byte0 = data.gearReq;
    Frame::data.Byte1 = data.unusedByte1;
    Frame::data.Byte2 = data.unusedByte2;
    Frame::data.Byte3 = data.unusedByte3;
    Frame::data.Byte4 = data.unusedByte4;
    Frame::data.Byte5 = data.unusedByte5;
    Frame::data.Byte6 = data.unusedByte6;
    Frame::data.Byte7 = data.flagByte.byte7;
}

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
        Frame5() {this->id = 5;}
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
        FrameData data;

        inline void write();
};

inline void Frame5::write() {
    Frame::data.Byte0 = data.engSts;
    Frame::data.Byte1 = data.unusedByte1;
    Frame::data.Byte2 = data.unusedByte2;
    Frame::data.Byte3 = data.unusedByte3;
    Frame::data.Byte4 = data.unusedByte4;
    Frame::data.Byte5 = data.unusedByte5;
    Frame::data.Byte6 = data.unusedByte6;
    Frame::data.Byte7 = data.flagByte.byte7;
}

//____Frame6_Gearbox_ECU______________________________________
struct rpmBits{
    uint8_t rpmLSB;
    uint8_t rpmMSB; 
};
union rpmByte{
    uint16_t RPMsignal = 0;
    rpmBits bytes;
};
class Frame6 : public Frame { 
    public:
        Frame6() {this->id = 60;}
        ~Frame6() = default;

        struct FrameData {
            uint8_t gearStick = 0; // 0-3 (P/R/N/D)
            rpmByte rpm; // uint16_t 0-10000 divided in MSB-LSB
            uint8_t engagedGear = 0;
            uint8_t unusedByte4 = 0;
            uint8_t unusedByte5 = 0;
            uint8_t unusedByte6 = 0;
            uint8_t unusedByte7 = 0;
        };
        FrameData data;

        inline void write();
};

inline void Frame6::write() {
    Frame::data.Byte0 = data.gearStick;
    Frame::data.Byte1 = data.rpm.bytes.rpmMSB;
    Frame::data.Byte2 = data.rpm.bytes.rpmLSB;
    Frame::data.Byte3 = data.engagedGear;
    Frame::data.Byte4 = data.unusedByte4;
    Frame::data.Byte5 = data.unusedByte5;
    Frame::data.Byte6 = data.unusedByte6;
    Frame::data.Byte7 = data.unusedByte7;
}

#endif

