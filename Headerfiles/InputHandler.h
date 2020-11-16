#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <iostream>
#include <cmath>
#include <utility>
#include "KeyboardReader.h"
#include "CanInput.h"

class InputHandler{
public:
    InputHandler();
    ~InputHandler(){reader.stop();}
    bool run(int cycleTime);
    KeyboardReader reader;
    canInput data;
    CANSender canSender;
};

#endif // INPUTHANDLER_H