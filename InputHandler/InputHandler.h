#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <iostream>
#include <cmath>
#include <utility>
#include "KeyboardReader.h"


struct user_input_signals{
    // Temp copy of SendCAN example
    //Frame 1 signals
    uint8_t BrkPdl = 0;
    uint8_t AccPdl = 0;
    //Frame 2 signal
    uint8_t Frame2 = 2;
    uint8_t GearReq = 0;
    //Frame 3 signals
    uint8_t StartBtn = 0;
    uint8_t Ignition = 0;
    //Frame 4 signal
    //uint8_t Speed = 50;
    //Frame 5 signals
    //uint8_t GearStick = 1;
    //uint16_t RPM = 9000;
};

class InputHandler{
public:
    InputHandler();
    ~InputHandler(){};
    bool run();
    void stop();
    KeyboardReader reader;
    user_input_signals data;
    // create CANWriter object
};





#endif // INPUTHANDLER_H