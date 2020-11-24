#include <iostream>
#include <thread>
#include <atomic>
#include "can_io.h"
#include "shared_memory.h"
#include "engine.h"
#include "gearbox.h"

std::atomic<bool> exitFlag;

void runCANIO(SharedMemory<Frame> *frame1, SharedMemory<Frame> *frame3, SharedMemory<Frame> *frame4,SharedMemory<Frame> *frame5,SharedMemory<Frame> *frame6)
{
    CANIO canIO;
    canIO.start_can();
    Frame5 can5Send;
    Frame6 can6Send;

    while(true) {
        bool terminate = canIO.readCANWriteToMemory(frame1, frame3, frame4);

        can5Send=frame5->read();
        canIO.frameToBus(&can5Send);
        can6Send=frame6->read();
        canIO.frameToBus(&can6Send);
        
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

/*void runCANIO(SharedMemory<CanInput> *canInMem, SharedMemory<CanOutput> *canOutMem)
{
    CANIO canIO;
    canIO.start_can();
    while(true) {
        bool terminate = canIO.readCANWriteToMemory(canInMem);
        
        CanOutput canSend=canOutMem->read();
        canIO.frameToBus(004, canSend.vhlSpeed);
        canIO.frameToBus(005, canSend.gearStick, canSend.RPM, canSend.engagedGear);
        canIO.frameToBus(007, canSend.engSts);

        if (exitFlag) {
            
            break;
        }

        // Sleep
        std::this_thread::sleep_for(std::chrono::microseconds(10000));
    }
}*/

void runVehicle(SharedMemory<Frame> *frame1, SharedMemory<Frame> *frame3, SharedMemory<Frame> *frame4, SharedMemory<Frame> *frame5, SharedMemory<Frame> *frame6) {
    Engine engine;
    Gearbox gearbox;
    Frame5 cframe;
    Frame6 cframe;

    const int timeStepSize = 10; // Milliseconds

    while(true) {
        // Fetch CAN Inputs from shared memory   
        const Frame1 cframe1 = frame1->read();
        const Frame2 cframe2 = frame2->read();
        const Frame3 cframe3 = frame3->read();
        const Frame4 cframe4 = frame4->read();
        cframe5 = frame5->read();
        cframe6 = frame6->read();

        // Run engine and gearbox simulation with CANIn and CANOut
        engine.run(&cframe1, &cframe3, &cframe4 , &cframe5, &cframe6, &timeStepSize);
        //gearbox.run(canIn, canOut, engine.getEngTrq(), engine.getEngSts(),timeStepSize);

        // Push CAN Output values to shared memory
        frame5->write(cframe5);
        frame6->write(cframe6);

        // Shutdown condition
        if (cframe1.data.quitEmul==1)
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
}*/


int main()
{    
    SharedMemory<Frame1> frame1;
    SharedMemory<Frame2> frame2;
    SharedMemory<Frame3> frame3;
    SharedMemory<Frame4> frame4;
    SharedMemory<Frame5> frame5;
    SharedMemory<Frame6> frame6; 
    //SharedMemory<CanInput> canInMem;   
    //SharedMemory<CanOutput> canOutMem;   
    exitFlag = false;
  
    std::thread t3(runCANIO, &frame1, &frame3, &frame4, &frame5, &frame6);
    std::thread t4(runVehicle, &frame1, &frame3, &frame4, &frame5, &frame6);

    //std::thread t3(runCANIO, &canInMem, &canOutMem);
    //std::thread t4(runVehicle, &canInMem, &canOutMem);

    t3.join();
    t4.join();
    return 0;
}
