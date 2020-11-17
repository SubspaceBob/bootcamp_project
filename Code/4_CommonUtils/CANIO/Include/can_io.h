#ifndef CANIO_H
#define CANIO_H
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include "socketcan_cpp.h"

struct CanInput
{
    int8_t brkPdl;
    int8_t accPdl;
    int8_t gearReq;
    int8_t startBtn;
    int8_t quitEmul;

    CanInput() {brkPdl=0; accPdl=0; gearReq=0; startBtn=0; quitEmul=0;}
};

struct CanOutput
{
    uint8_t vhlSpeed;
    uint8_t gearStick;
    uint16_t RPM;

    CanOutput() {vhlSpeed=2; gearStick=0; RPM=0;}
};

struct SharedMemory
{
    std::shared_mutex can_input_mutex;
    std::shared_mutex can_output_mutex;
    CanInput can_input;
    CanOutput can_Output;

    void save_can_input(scpp::CanFrame fr)
    {
        std::unique_lock lock(can_input_mutex);
        if(fr.id==001)
        {
            can_input.brkPdl=fr.data[0];
            can_input.accPdl=fr.data[1];
        }  
        else if(fr.id==002)
        {
            can_input.gearReq=fr.data[0];
        } 
        else if(fr.id==003)
        {
            can_input.startBtn=fr.data[0];
            can_input.quitEmul=fr.data[1];
        }
        
    }

    CanInput read_input_memory()
    {
        std::shared_lock lock(can_input_mutex);
        return can_input;
    }

    void write_can_output(CanOutput output)
    {
        std::unique_lock lock(can_output_mutex);
        can_Output.gearStick=output.gearStick;
        can_Output.RPM=output.RPM;
        can_Output.vhlSpeed=output.vhlSpeed;
        //std::cout << "Writing to shared memory " << std::endl << std::flush;
    }
    
    CanOutput read_output_memory()
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
    bool readCANWriteToMemory(SharedMemory *memory);
    void frameToBus(uint8_t frameNo, uint8_t signalValue);
    void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint8_t signal2Value);
    void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value);
};
#endif
