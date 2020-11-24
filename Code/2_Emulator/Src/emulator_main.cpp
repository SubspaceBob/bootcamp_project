#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "can_io.h"
#include "shared_memory.h"
#include "engine.h"
#include "gearbox.h"

std::atomic<bool> exitFlag;

// Add possible to configure size and CanIn/CanOut from elsewhere (database parser)
// possible to add map for easy access to specific frame number
std::vector<SharedMemory<Frame>> SharedFrameMemoryVector(6); 
uint8_t CanInFrames[] = {0, 1, 2, 3, 4};
uint8_t CanOutFrames[] = {5, 6};

void runCANIO()
{
    CANIO canIO;
    canIO.start_can();
    Frame5 can5Send;
    Frame6 can6Send;

    while(true) {
        bool read_ok = canIO.readCANWriteToMemory(SharedFrameMemoryVector, CanInFrames); 


        /*can5Send=frame5->read();
        canIO.frameToBus(&can5Send);
        can6Send=frame6->read();
        canIO.frameToBus(&can6Send);
        */

        //CanOutput canSend=canOutMem->read();
        //canIO.frameToBus(004, canSend.vhlSpeed);
        //canIO.frameToBus(005, canSend.gearStick, canSend.RPM, canSend.engagedGear);
        //canIO.frameToBus(007, canSend.engSts);

        if (exitFlag) {
            
            break;
        }

        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }
}

void runVehicle() {
    std::vector<Frame> frames (6); // Configure from same place as SharedMemory!
    Engine engine;
    Gearbox gearbox;

    const int timeStepSize = 10; // Milliseconds

    while(true) {
        // Fetch CAN Inputs from shared memory   
        for(const int &index : CanInFrames)
            frames[index] = SharedFrameMemoryVector[index].read();
            
        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(frames, timeStepSize);
        gearbox.run(frames, engine.getEngTrq(), engine.getEngSts(),timeStepSize);

        // Push CAN Output values to shared memory
        for(const int &index : CanOutFrames)
            SharedFrameMemoryVector[index].write(frames[index]);

        // Shutdown condition
        //if (cframe1.data.quitEmul==1)
        if (frames[6].data.Byte0 == 1) // Very hardcoded for now...
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
    exitFlag = false;
  
    std::thread t3(runCANIO);
    std::thread t4(runVehicle);

    t3.join();
    t4.join();
    return 0;
}
