#include <iostream>
#include <thread>
#include "CanInput.h"
#include "engine.h"
#include "GearClass.h"
#include <atomic>

std::atomic<bool> something;
void runCANIO(SharedMemory *memory)
{
    CANIO canIO;
    canIO.start_can();
    while(true) {
        bool terminate = canIO.ReadCANWriteToMemory(memory);

        canOutput canSend=memory->read_output_memory();
        canIO.frameToBus(005, canSend.GearStickPos, canSend.RPM);
        canIO.frameToBus(004, canSend.VehicleSpeed);

        if (something) {
            
            break;
        }

        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }
}

void runVehicle(SharedMemory *memory){
    canOutput CANOut;
    Engine engine;
    Gearbox gearbox;
    int TimeStepSize = 10; // Milliseconds

    while(true) {
        // Fetch CAN Input from shared memory
        canInput CANIn = memory->read_input_memory();
        
        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(CANIn, CANOut, gearbox.getRPS(), TimeStepSize, (int) gearbox.getGearStick());
        gearbox.run(CANIn, CANOut, engine.getEngTrq(), TimeStepSize);

        // Push CAN Output values to shared memory
        memory->write_can_output(CANOut);

        // Shutdown condition
        if (CANIn.QuitEmul==1)
        {
            something.exchange(true);
            break;
        }

        // Sleep, use same time as TimeStepSize in run-methods to get approximate Real-time
        std::this_thread::sleep_for(std::chrono::milliseconds(TimeStepSize));
    }
}


int main()
{    
    SharedMemory memory;   
    something = false;
  
    std::thread t3(runCANIO, &memory);
    std::thread t4(runVehicle, &memory);

    t3.join();
    t4.join();
    return 0;
}
