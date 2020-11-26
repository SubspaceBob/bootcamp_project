#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include "can_io.h"
#include "shared_memory.h"
#include "engine.h"
#include "gearbox.h"
#include "database.h"

std::atomic<bool> exitFlag;
// Add possible to configure size and CanIn/CanOut from elsewhere (database parser)
// possible to add map for easy access to specific frame number
std::vector<SharedMemory<Frame>> SharedFrameMemoryVector(6); 
CANDatabaseInfo dbInfo;

void runCANIO()
{
    
    CANIO canIO;
    canIO.start_can();
    Frame5 can5Send;
    Frame6 can6Send;

    while(true) {
        bool read_ok = canIO.readCANWriteToMemory(SharedFrameMemoryVector, dbInfo); 


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
    std::vector<Frame> frames (7); // Configure from same place as SharedMemory!
    Engine engine;
    Gearbox gearbox;

    const int timeStepSize = 10; // Milliseconds

    while(true) {
        // Fetch CAN Inputs from shared memory   
        for(Frame frame : dbInfo.canInFrames)
            frame = std::move(SharedFrameMemoryVector[frame.id].read());
            
        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(dbInfo, timeStepSize);
        gearbox.run(dbInfo, engine.getEngTrq(), engine.getEngSts(),timeStepSize);

        // Push CAN Output values to shared memory
        for(const Frame frame : dbInfo.canOutFrames)
            SharedFrameMemoryVector[frame.id].write(frame);

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
    dbInfo = CANDatabaseInfo();
    dbInfo.hardcodedSetup();
  
    std::thread t3(runCANIO);
    std::thread t4(runVehicle);

    t3.join();
    t4.join();
    return 0;
}
