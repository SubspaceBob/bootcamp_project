#ifndef CANINPUT_H
#define CANINPUT_H
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include "socketcan_cpp.h"


struct canInput
{
    int8_t BrakePdl;
    int8_t AccPdl;
    int8_t GearReq;
    int8_t StartBtn;
    int8_t Ignition;

    canInput() {BrakePdl=0; AccPdl=0; GearReq=0; StartBtn=0; Ignition=0;}

};

struct SharedMemory
{
    std::shared_mutex can_input_mutex;
    canInput can_input;

    void save_can_input(scpp::CanFrame fr){
        std::unique_lock lock(can_input_mutex);
        if(fr.id==001){
            can_input.BrakePdl=fr.data[0];
            can_input.AccPdl=fr.data[1];
        }  
        else if(fr.id==002){
            can_input.GearReq=fr.data[0];
        } 
        else if(fr.id==003){
            can_input.StartBtn=fr.data[0];
            can_input.Ignition=fr.data[1];
        }
        
    }

    canInput read_memory(){
        std::shared_lock lock(can_input_mutex);
        std::cout << "Reading from shared memory " << std::endl << std::flush;
        return can_input;
    }
};

class CANReader{
public:
    CANReader() = default;
    ~CANReader() = default;
    scpp::SocketCan sockat_can;
    bool start_can();
    bool ReadCANWriteToMemory(SharedMemory *memory);
};


#endif