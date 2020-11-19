#include <iostream>
#include "can_io.h"
#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

struct Bitfield{
    uint8_t rpmLSB;
    uint8_t rpmMSB; 
};
union RPM{
    uint16_t rpmIn;
    Bitfield rpmOut;
};

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

bool CANIO::readCANWriteToMemory(SharedMemory *memory) {
    bool retval=false;
    scpp::CanFrame fr;
    if (sockat_can.read(fr) == scpp::STATUS_OK) { 
        memory->save_can_input(fr);
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

// Frame with 1 uint8 signal & 1 uint16 signal...
void CANIO::frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value) {

    RPM rpm;
    rpm.rpmIn= signal2Value;
    scpp::CanFrame cf_to_write; 
    cf_to_write.id = frameNo;
    cf_to_write.len = 8;

    // Output signal values...
    cf_to_write.data[0] = signal1Value;
    cf_to_write.data[1] = rpm.rpmOut.rpmMSB;
    cf_to_write.data[2] = rpm.rpmOut.rpmLSB;
    // ...And rest to 0
    for (int i = 3; i < 8; ++i)
        cf_to_write.data[i] = 0x00;
    auto write_sc_status = sockat_can.write(cf_to_write);

    if (write_sc_status != scpp::STATUS_OK)
        printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
}

