#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <iostream>
#include <cmath>
#include <utility>
#include "KeyboardReader.h"

struct user_input_signals{
    //Frame 1 signals
    uint8_t Frame1 = 001;
    uint8_t BrkPdl = 0;
    uint8_t AccPdl = 0;
    //Frame 2 signal
    uint8_t Frame2 = 002;
    uint8_t GearReq = 0;
    //Frame 3 signals
    uint8_t Frame3 = 003;
    uint8_t StartBtn = 0;
    uint8_t Ignition = 0;
};

class InputHandler{
public:
    InputHandler();
    ~InputHandler(){reader.stop();}
    bool run(int cycleTime);
    KeyboardReader reader;
    user_input_signals data;
    // create CANWriter object
};

#endif // INPUTHANDLER_H