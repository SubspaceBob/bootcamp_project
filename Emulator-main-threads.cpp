#include <iostream>
#include <thread>
#include "CanInput.h"
#include "engine.h"
#include "GearClass.h"
#include "frameToBus.h"
#include <atomic>



std::atomic<bool> something;
void runCANIO(SharedMemory *memory)
{
    CANReader canReader;
    canReader.start_can();
    while(true) {
        bool terminate = canReader.ReadCANWriteToMemory(memory);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        //FramePacker(Engine, Gearbox);
        if (something) {
            
            break;
        }
    }
}

void runVehicle(SharedMemory *memory){
    Engine engine;
    Gearbox gearbox;
    int TimeStepSize = 10; // Milliseconds

    while(true) {
        canInput from_memory = memory->read_memory();
        std::cout << "AccPdl: " << (int)from_memory.AccPdl << std::endl << std::flush;
                
        engine.run(from_memory, gearbox.getRPS(), TimeStepSize);
        gearbox.run(from_memory, engine.getEngTrq(), TimeStepSize);
        if (from_memory.Ignition==1)
        {
            something.exchange(true);
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TimeStepSize));
        
    }
}


int main(){
    
    SharedMemory memory;
    
    something = false;

  
    std::thread t3(runCANIO, &memory);
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

