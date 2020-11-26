#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>


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

//____Frame6_Gearbox_ECU______________________________________
struct Bitfield{
    uint8_t rpmLSB;
    uint8_t rpmMSB; 
};
union RPM{
    uint16_t RPMsignal = 0;
    Bitfield bytes;
};


struct CANDatabaseInfo{
    CANDatabaseInfo () = default;
    ~CANDatabaseInfo() = default;
    // signals should be pointers and length, not uint8_t!
    std::map<std::string, uint8_t> signals;
    std::map<std::string, Frame> frames;

    // FrameGroups
    std::vector<Frame> iHCanTXFrames;   // Frames are only used by sending/recieveing CAN and read/write memory
    std::vector<Frame> emuCanRXFrames;  // Frames are not used by "application", 
    std::vector<Frame> emuCanTXFrames;  // different FrameGroups share frames (ecu1_1_RX = ecu2_2_TX = ecu_3_1_TX)
    std::vector<Frame> guiCanRXFrames;

    Frame *getFrame(std::vector<Frame> *FrameGroup, const uint32_t &id)
    {
        for(Frame &elem: (*FrameGroup))
        {
            if (elem.id == id)
            {
                return &elem;
            }
            else
            {
                return nullptr;
            }
        }
    }

    void hardcodedSetup()
    {
        // This information should be generated by a dbc-parser.
        // Define frames, name defined by sender
        frames["ih_1"] = Frame();   // set frame ID in constructor!
        frames["ih_2"] = Frame();  
        frames["ih_3"] = Frame();
        frames["ih_4"] = Frame();
        frames["ih_5"] = Frame();
        frames["ih_6"] = Frame();
        frames["emu_1"] = Frame();
        frames["emu_2"] = Frame();

        // Define signals, used by applications
        signals["startBtn"]     = frames["ih_1"]->data.Byte0;
        signals["quitEmul"]     = frames["ih_1"]->data.Byte1;
        signals["handBrk"]      = frames["ih_2"]->data.Byte0;
        signals["abs"]          = frames["ih_2"]->data.Byte1;
        signals["brkPdl"]       = frames["ih_3"]->data.Byte0;
        signals["accPdl"]       = frames["ih_3"]->data.Byte1;
        signals["gearReq"]      = frames["ih_4"]->data.Byte0;
        signals["engSts"]       = frames["emu_1"]->data.Byte0;
        signals["gearStick"]    = frames["emu_2"]->data.Byte0;
        signals["engagedGear"]  = frames["emu_2"]->data.Byte1;

        // Add pointer to frames in different groups
        iHCanTXFrames.push_back(frames["ih_1"]);
        iHCanTXFrames.push_back(frames["ih_2"]); 
        iHCanTXFrames.push_back(frames["ih_3"]); 
        iHCanTXFrames.push_back(frames["ih_4"]);
        iHCanTXFrames.push_back(frames["ih_5"]); 
        iHCanTXFrames.push_back(frames["ih_6"]);

        emuCanRXFrames.push_back(frames["ih_1"]);
        emuCanRXFrames.push_back(frames["ih_2"]); 
        emuCanRXFrames.push_back(frames["ih_3"]); 
        emuCanRXFrames.push_back(frames["ih_4"]); 

        emuCanTXFrames.push_back(frames["emu_1"]);
        emuCanTXFrames.push_back(frames["emu_2"]);

        guiCanRXFrames.push_back(frames["ih_5"]);
        guiCanRXFrames.push_back(frames["ih_6"]);
    }
};

#endif