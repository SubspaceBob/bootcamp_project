#include <iostream>
#include <thread>
#include <atomic>
#include "can_io.h"
#include "engine.h"
#include "gearbox.h"

std::atomic<bool> exitFlag;
void runCANIO(SharedMemory *memory)
{
    CANIO canIO;
    canIO.start_can();
    while(true) {
        bool terminate = canIO.readCANWriteToMemory(memory);

        CanOutput canSend=memory->read_output_memory();
        canIO.frameToBus(005, canSend.gearStick, canSend.RPM);
        canIO.frameToBus(004, canSend.vhlSpeed);

        if (exitFlag) {
            
            break;
        }

        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }
}

void runVehicle(SharedMemory *memory){
    CanOutput canOut;
    Engine engine;
    Gearbox gearbox;
    int timeStepSize = 10; // Milliseconds

    while(true) {
        // Fetch CAN Input from shared memory
        CanInput canIn = memory->read_input_memory();
        
        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(canIn, canOut, gearbox.getRPS(), timeStepSize, (int) gearbox.getGearStick());
        gearbox.run(canIn, canOut, engine.getEngTrq(), timeStepSize);

        // Push CAN Output values to shared memory
        memory->write_can_output(canOut);

        // Shutdown condition
        if (canIn.quitEmul==1)
        {
            exitFlag.exchange(true);
            break;
        }

        // Sleep, use same time as TimeStepSize in run-methods to get approximate Real-time
        std::this_thread::sleep_for(std::chrono::milliseconds(timeStepSize));
    }
}


int main()
{    
    SharedMemory memory;   
    exitFlag = false;
  
    std::thread t3(runCANIO, &memory);
    std::thread t4(runVehicle, &memory);

    t3.join();
    t4.join();
    return 0;
}
