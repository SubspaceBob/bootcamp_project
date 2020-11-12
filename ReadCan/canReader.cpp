#include <iostream>
#include "CanInput.h"
#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp



bool CANReader::start_can(){
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

bool CANReader::ReadCANWriteToMemory(SharedMemory *memory) {
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
