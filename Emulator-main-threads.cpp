#include <iostream>
#include <thread>
#include "CanInput.h"
#include "engine.h"
#include "GearClass.h"
#include "frameToBus.h"
#include <atomic>

std::atomic<bool> something;
void runCANIO(SharedMemory *memory, CANReader *canReader)
{
    
    while(true) {
        bool terminate = canReader->ReadCANWriteToMemory(memory);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //FramePacker(Engine, Gearbox);
        if (something) {
            
            break;
        }
    }
}

void runVehicle(SharedMemory *memory){
    while(true) {
        canInput from_memory = memory->read_memory();
        std::cout << "Gear Request: " << (int)from_memory.GearReq << std::endl << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        engine.run(from_memory);
        gearbox.run(from_memory, engine);
        if (from_memory.Ignition==1)
        {
            something.exchange(true);
            break;
        }
    }
}


int main(){
    CANReader canReader;
    SharedMemory memory;
    Engine engine;
    Gearbox gearbox;
    something = false;

    canReader.start_can();
    std::thread t3(runCANIO, &memory, &canReader);
    std::thread t4(runVehicle, &memory);

    t3.join();
    t4.join();
    return 0;
}


    
/*
class EmuMainThreads{
public:
    EmuMainThreads() = default;
    ~EmuMainThreads(){};
    canInput inputVal;
    Engine Engine;
    Gearbox Gearbox;
    bool error=false;

    void runCANReader();
    void runVehicle();
};

void EmuMainThreads::runCANReader(){
}

void EmuMainThreads::runVehicle(){
}*/

