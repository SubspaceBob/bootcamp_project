#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>

class Frame{
    public:
        uint8_t id;
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
        
        Frame(int id){id=id;}
        virtual ~Frame() = default;

        virtual void write(class Frame input);
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
        Frame1() : Frame(1){}
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

        inline void write(class Frame1 input);
};

inline void Frame1::write(class Frame1 input) {
    data.startBtn    = input.data.startBtn;
    data.quitEmul    = input.data.quitEmul;
    data.unusedByte2 = input.data.unusedByte2;
    data.unusedByte3 = input.data.unusedByte3;
    data.unusedByte4 = input.data.unusedByte4;
    data.unusedByte5 = input.data.unusedByte5;
    data.unusedByte6 = input.data.unusedByte6;
    data.flagByte    = input.data.flagByte;
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
class Frame2  : public Frame {
    public:
        Frame2() : Frame(2){}
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

        inline void write(class Frame2 input);
};

inline void Frame2::write(class Frame2 input) {
    data.unusedByte0 = input.data.unusedByte0;
    data.unusedByte1 = input.data.unusedByte1;
    data.unusedByte2 = input.data.unusedByte2;
    data.unusedByte3 = input.data.unusedByte3;
    data.unusedByte4 = input.data.unusedByte4;
    data.unusedByte5 = input.data.unusedByte5;
    data.unusedByte6 = input.data.unusedByte6;
    data.flagByte    = input.data.flagByte;
}


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
        Frame3() : Frame(3){}
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

        inline void write(class Frame3 input);
};

inline void Frame3::write(class Frame3 input) {
    data.brkPdl      = input.data.brkPdl;
    data.accPdl      = input.data.accPdl;
    data.unusedByte2 = input.data.unusedByte2;
    data.unusedByte3 = input.data.unusedByte3;
    data.unusedByte4 = input.data.unusedByte4;
    data.unusedByte5 = input.data.unusedByte5;
    data.unusedByte6 = input.data.unusedByte6;
    data.flagByte    = input.data.flagByte;
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
class Frame4  : public Frame { 
    public:
        Frame4() : Frame(4){}
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
        FrameData data;

        inline void write(class Frame4 input);
};

inline void Frame4::write(class Frame4 input) {
    data.gearReq     = input.data.gearReq;
    data.unusedByte1 = input.data.unusedByte1;
    data.unusedByte2 = input.data.unusedByte2;
    data.unusedByte3 = input.data.unusedByte3;
    data.unusedByte4 = input.data.unusedByte4;
    data.unusedByte5 = input.data.unusedByte5;
    data.unusedByte6 = input.data.unusedByte6;
    data.flagByte    = input.data.flagByte;
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
        Frame5() : Frame(5){}
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

        inline void write(class Frame5 input);
};

inline void Frame5::write(class Frame5 input) {
    data.engSts      = input.data.engSts;
    data.unusedByte1 = input.data.unusedByte1;
    data.unusedByte2 = input.data.unusedByte2;
    data.unusedByte3 = input.data.unusedByte3;
    data.unusedByte4 = input.data.unusedByte4;
    data.unusedByte5 = input.data.unusedByte5;
    data.unusedByte6 = input.data.unusedByte6;
    data.flagByte    = input.data.flagByte;
}

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
        Frame6() : Frame(6){}
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
        FrameData data;

        inline void write(class Frame6 input);
};

inline void Frame6::write(class Frame6 input) {
    data.gearStick        = input.data.gearStick;
    data.rpm.bytes.rpmMSB = input.data.rpm.bytes.rpmMSB;
    data.rpm.bytes.rpmLSB = input.data.rpm.bytes.rpmLSB;
    data.engagedGear      = input.data.engagedGear;
    data.unusedByte4      = input.data.unusedByte4;
    data.unusedByte5      = input.data.unusedByte5;
    data.unusedByte6      = input.data.unusedByte6;
    data.unusedByte7      = input.data.unusedByte7;
}

#endif

