#include <iostream>
#include <thread>
#include <atomic>
#include "can_io.h"
#include "shared_memory.h"
#include "engine.h"
#include "gearbox.h"

std::atomic<bool> exitFlag;
const int timeStepSize = 10; // Milliseconds
SharedMemory<Frame1> frame1Mem;   
SharedMemory<Frame3> frame3Mem;
SharedMemory<Frame4> frame4Mem;
SharedMemory<Frame5> frame5Mem;
SharedMemory<Frame6> frame6Mem;

void writeToBus(CANIO &canIO){
    // Read the output from runVehicle
    canIO.frame5 = frame5Mem.read();
    canIO.frame6 = frame6Mem.read();
    // Prep it for output = translate it to a frame parent style
    canIO.frame5.write(canIO.frame5);
    canIO.frame6.write(canIO.frame6);
    //And send it
    canIO.frameToBus(canIO.frame5);
    canIO.frameToBus(canIO.frame6);
}

void runCANIO()
{
    CANIO canIO;
    canIO.start_can();
    
    while(true) {
        // Read a new frame
        int incFrame = canIO.readCAN();

        // Save it to the right memory
        if (incFrame == 1) {
            frame1Mem.write(canIO.frame1);
            std::cout << "writing to frame1mem " << (unsigned int)canIO.frame1.data.startBtn <<" "
                << (unsigned int)canIO.frame1.data.quitEmul << std::endl;}
        else if (incFrame == 3) frame3Mem.write(canIO.frame3);
        else if (incFrame == 4) frame4Mem.write(canIO.frame4);

        // Read the result from runVehicle and send it out on the bus 
        writeToBus(canIO);

        if (exitFlag) {     
            break;
        }

        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(timeStepSize));
    }
}


/*void runCANIO(SharedMemory<CanInput> *canInMem, SharedMemory<CanOutput> *canOutMem)
{
    CANIO canIO;

    canIO.start_can();
    while(true) {
        bool terminate = canIO.readCANWriteToMemory(canInMem);
        
        CanOutput canSend=canOutMem->read();
        
        // Step 1 in new database Start by transferring outputs to new frames
        frame5.data.engSts = canSend.engSts;
        frame6.data.engagedGear = canSend.engagedGear;
        frame6.data.gearStick = canSend.gearStick;
        frame6.data.rpm.RPMsignal = canSend.RPM;

        frame5.write();
        frame6.write();
        canIO.frameToBus(frame5);
        canIO.frameToBus(frame6);
        //canIO.frameToBus(004, canSend.vhlSpeed);
        //canIO.frameToBus(005, canSend.gearStick, canSend.RPM, canSend.engagedGear);
        //canIO.frameToBus(007, canSend.engSts);

        if (exitFlag) {
            
            break;
        }

        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }
}*/

void runVehicle(){
    Frame1 frame1;
    Frame3 frame3;
    Frame4 frame4;
    Frame5 frame5;
    Frame6 frame6;

    Engine engine;
    Gearbox gearbox;
    
    while(true) {
        // Fetch CAN Input from shared memory
        frame1 = frame1Mem.read();
        std::cout << "read frame1mem " << (unsigned int)frame1.data.startBtn <<" "
                << (unsigned int)frame1.data.quitEmul << std::endl;
        frame3 = frame3Mem.read();
        frame4 = frame4Mem.read();
        
        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(frame1, frame3, frame4, frame5, frame6, frame5Mem);
        gearbox.run(frame1, frame3, frame4, frame5, frame6, frame6Mem, timeStepSize);

        // Shutdown condition
        if (frame1.data.quitEmul==1)
        {
            exitFlag.exchange(true);
            break;
        }

        // Sleep, use same time as TimeStepSize in run-methods to get approximate Real-time
        std::this_thread::sleep_for(std::chrono::milliseconds(timeStepSize));
    }
}



/*void runVehicle(SharedMemory<CanInput> *canInMem, SharedMemory<CanOutput> *canOutMem){
    CanOutput canOut;
    Engine engine;
    Gearbox gearbox;
    int timeStepSize = 10; // Milliseconds

    while(true) {
        // Fetch CAN Input from shared memory
        CanInput canIn = canInMem->read();


        //std::cout << "canIn.accPdl : " << static_cast<int>(canIn.accPdl) << std::endl;
        
        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(canIn, canOut, gearbox.getRPS(), timeStepSize, (int) gearbox.getGearStick());
        gearbox.run(canIn, canOut, engine.getEngTrq(), engine.getEngSts(),timeStepSize);

        // Push CAN Output values to shared memory
        canOutMem->write(canOut);

        // Shutdown condition
        if (canIn.quitEmul==1)
        {
            exitFlag.exchange(true);
            break;
        }

        // Sleep, use same time as TimeStepSize in run-methods to get approximate Real-time
        std::this_thread::sleep_for(std::chrono::milliseconds(timeStepSize));
    }
} */


int main()
{    
    //SharedMemory<CanInput> canInMem;   
    //SharedMemory<CanOutput> canOutMem;  

    exitFlag = false;

    std::thread t1(runCANIO);
    std::thread t2(runVehicle);

    t1.join();
    t2.join();

    /*std::thread t3(runCANIO, &canInMem, &canOutMem);
    std::thread t4(runVehicle, &canInMem, &canOutMem);

    t3.join();
    t4.join();*/
    return 0;
}
