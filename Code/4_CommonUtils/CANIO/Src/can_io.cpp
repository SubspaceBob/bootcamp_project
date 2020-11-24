#include <iostream>
#include <algorithm>
#include <find>
#include <move>
#include <vector>
#include "can_io.h"
#include "../../SharedMemory/Include/shared_memory.h"
#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp


 //Replaced by database frame1-6
void CanInput::write(CanInput input)
{
    brkPdl=input.brkPdl;
    accPdl=input.accPdl;
    gearReq=input.gearReq;
    startBtn=input.startBtn;
    quitEmul=input.quitEmul;
}

void CanOutput::write(CanOutput output)
{
    gearStick=output.gearStick;
    RPM=output.RPM;
    vhlSpeed=output.vhlSpeed;
    engagedGear=output.engagedGear;
    engSts=output.engSts;
    //std::cout << "Writing to shared memory " << std::endl << std::flush;
}

bool CANIO::start_can(){
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        return false;
    }
    else
    {
        std::cout << "CANReader vcan0 open." << std::endl;
        return true;
    }
    
}

//generalize to get only data pointer
bool CANIO::readCANWriteToMemory(std::vector<SharedMemory<Frame>> &SharedFrameMemoryVector, uint8_t CanInFrames[]) {
    bool retval=false;
    scpp::CanFrame fr;
    if (sockat_can.read(fr) == scpp::STATUS_OK) {

        // using std::begin/end instead of size of array as argument
        // if fr.id is any_of CanInFrames
        if (std::any_of(std::begin(CanInFrames), std::end(CanInFrames), [&](int fr.id))) 
        {
            // Set the data according to frame

            canIn.id = fr.id;
            canIn.data = fr.data;
            
            // Ẃrite it to memory
            SharedFrameMemoryVector[fr.id]->write(canIn);

            // TODO: Not actually used clean up
            // And set bool return according to q btn.
            retval = true;
        }
    }
    else
    {
        std::cout << "CANReader read STATUS not OK!!" << std::endl;
    }
    return (retval);
}

void CANIO::frameToBus(SharedMemory<Frame> *frame) {
    scpp::CanFrame cf_to_write;

    // Set Frame ID   
    cf_to_write.id = frame->memory.id;
    cf_to_write.len = 8;
    // Output signal value...
    cf_to_write.data[0] = frame->memory.data.Byte0;
    cf_to_write.data[1] = frame->memory.data.Byte1;
    cf_to_write.data[2] = frame->memory.data.Byte2;
    cf_to_write.data[3] = frame->memory.data.Byte3;
    cf_to_write.data[4] = frame->memory.data.Byte4;
    cf_to_write.data[5] = frame->memory.data.Byte5;
    cf_to_write.data[6] = frame->memory.data.Byte6;
    cf_to_write.data[7] = frame->memory.data.Byte7;

    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
}


// Frame with 1 uint8 signal...
void CANIO::frameToBus(uint8_t frameNo, uint8_t signalValue) {
    scpp::CanFrame cf_to_write;

    // Set Frame ID   
    cf_to_write.id = frameNo;
    cf_to_write.len = 8;
    // Output signal value...
    cf_to_write.data[0] = signalValue;
    // ...And rest to 0
    for (int i = 1; i < 8; ++i)
        cf_to_write.data[i] = 0x00;
    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
}

// Frame with 2 uint8 signals...
void CANIO::frameToBus(uint8_t frameNo, uint8_t signal1Value, uint8_t signal2Value) {

    scpp::CanFrame cf_to_write; 
    cf_to_write.id = frameNo;
    cf_to_write.len = 8;

    // Output signal values...
    cf_to_write.data[0] = signal1Value;
    cf_to_write.data[1] = signal2Value;
    // ...And rest to 0
    for (int i = 2; i < 8; ++i)
        cf_to_write.data[i] = 0x00;
    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));    
}

// Frame 5...
void CANIO::frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value, uint8_t signal3Value) {
    //in dataBase Frame6
    struct Bitfield{
        uint8_t LSB;
        uint8_t MSB; 
    };
    union rpm{
        uint16_t In;
        Bitfield Out;
    };

    rpm rpm;
    rpm.In= signal2Value;
    scpp::CanFrame cf_to_write; 
    cf_to_write.id = frameNo;
    cf_to_write.len = 8;

    // Output signal values...
    cf_to_write.data[0] = signal1Value;
    cf_to_write.data[1] = rpm.Out.MSB;
    cf_to_write.data[2] = rpm.Out.LSB;
    cf_to_write.data[3] = signal3Value;
    // ...And rest to 0
    for (int i = 4; i < 8; ++i)
        cf_to_write.data[i] = 0x00;
    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
}


