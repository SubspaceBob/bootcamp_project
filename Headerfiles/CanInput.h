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

struct canOutput
{
    uint8_t VehicleSpeed;
    uint8_t GearStickPos;
    uint16_t RPM;

    canOutput() {VehicleSpeed=2; GearStickPos=0; RPM=0;}
};

struct SharedMemory
{
    std::shared_mutex can_input_mutex;
    std::shared_mutex can_output_mutex;
    canInput can_input;
    canOutput can_Output;

    void save_can_input(scpp::CanFrame fr)
    {
        std::unique_lock lock(can_input_mutex);
        if(fr.id==001)
        {
            can_input.BrakePdl=fr.data[0];
            can_input.AccPdl=fr.data[1];
        }  
        else if(fr.id==002)
        {
            can_input.GearReq=fr.data[0];
        } 
        else if(fr.id==003)
        {
            can_input.StartBtn=fr.data[0];
            can_input.Ignition=fr.data[1];
        }
        
    }

    canInput read_input_memory()
    {
        std::shared_lock lock(can_input_mutex);
        return can_input;
    }

    void write_can_output(canOutput output)
    {
        std::unique_lock lock(can_output_mutex);
        can_Output.GearStickPos=output.GearStickPos;
        can_Output.RPM=output.RPM;
        can_Output.VehicleSpeed=output.VehicleSpeed;
        //std::cout << "Writing to shared memory " << std::endl << std::flush;
    }
    
    canOutput read_output_memory()
    {
        std::shared_lock lock(can_output_mutex);
        //std::cout << "Reading from shared memory " << std::endl << std::flush;
        return can_Output;
    }
};

class CANIO{
public:
    CANIO() = default;
    ~CANIO() = default;
    scpp::SocketCan sockat_can;
    bool start_can();
    bool ReadCANWriteToMemory(SharedMemory *memory);
    void frameToBus(uint8_t frameNo, uint8_t signalValue);
    void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint8_t signal2Value);
    void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value);
};
#endif
