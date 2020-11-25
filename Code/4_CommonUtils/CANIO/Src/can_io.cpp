#include <iostream>
#include "can_io.h"
#include "../../SharedMemory/Include/shared_memory.h"
#include "socketcan_cpp.h"
#include "database.h"
// https://github.com/siposcsaba89/socketcan-cpp

struct Bitfield{
    uint8_t rpmLSB;
    uint8_t rpmMSB; 
};
union RPM{
    uint16_t rpmIn;
    Bitfield rpmOut;
};

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
bool CANIO::readCANWriteToMemory(SharedMemory<CanInput> *canInMem) {
    bool retval=false;
    scpp::CanFrame fr;
    if (sockat_can.read(fr) == scpp::STATUS_OK) { 
        if(fr.id==001)
        {
            canIn.brkPdl=fr.data[0];
            canIn.accPdl=fr.data[1];
        }  
        else if(fr.id==002)
        {
            canIn.gearReq=fr.data[0];
        } 
        else if(fr.id==003)
        {
            canIn.startBtn=fr.data[0];
            canIn.quitEmul=fr.data[1];
        }

        canInMem->write(canIn);

        if (fr.id==3 && fr.data[1]==1){
            retval = true;
        }
    }
    else
    {
        std::cout << "CANReader read STATUS not OK!!" << std::endl;
    }
    return (retval);
}

void CANIO::frameToBus(const Frame &frame) {
    scpp::CanFrame cf_to_write;

    // Set Frame ID   
    cf_to_write.id = frame.id;
    cf_to_write.len = 8;
    // Output signal value...
    cf_to_write.data[0] = frame.data.Byte0;
    cf_to_write.data[1] = frame.data.Byte1;
    cf_to_write.data[2] = frame.data.Byte2;
    cf_to_write.data[3] = frame.data.Byte3;
    cf_to_write.data[4] = frame.data.Byte4;
    cf_to_write.data[5] = frame.data.Byte5;
    cf_to_write.data[6] = frame.data.Byte6;
    cf_to_write.data[7] = frame.data.Byte7;

    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write (Frame type), error code : %d \n", int32_t(write_sc_status));
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

    RPM rpm;
    rpm.rpmIn= signal2Value;
    scpp::CanFrame cf_to_write; 
    cf_to_write.id = frameNo;
    cf_to_write.len = 8;

    // Output signal values...
    cf_to_write.data[0] = signal1Value;
    cf_to_write.data[1] = rpm.rpmOut.rpmMSB;
    cf_to_write.data[2] = rpm.rpmOut.rpmLSB;
    cf_to_write.data[3] = signal3Value;
    // ...And rest to 0
    for (int i = 4; i < 8; ++i)
        cf_to_write.data[i] = 0x00;
    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
}

