// This file is an example executable that shows how
// to output items on the CAN bus. This file is NOT
// I repeat: NOT! intended for the complete SW.
// use command make and make run to see it work and
// make clean to remove the leftovers when you're done.

#include <iostream>
#include "../socketcan_cpp/socketcan_cpp.h"

void frameToBus(uint8_t frameNo, uint8_t signalValue);
void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint8_t signal2Value);
void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value);

int main(){
    //Frame 1 signals
    uint8_t BrkPdl = 50;
    uint8_t AccPdl = 50;
    //Frame 2 signal
    uint8_t Frame2 = 002;
    uint8_t GearReq = 3;
    //Frame 3 signals
    uint8_t StartBtn = 1;
    uint8_t Ignition = 1;
    //Frame 4 signal
    uint8_t Speed = 50;
    //Frame 5 signals
    uint8_t GearStick = 1;
    uint16_t RPM = 9000;
     
    frameToBus(001, BrkPdl, AccPdl);
    frameToBus(Frame2, GearReq);
    frameToBus(003, StartBtn, Ignition);
    frameToBus(004, Speed);
    frameToBus(005, GearStick, RPM);

    return 0; 
}