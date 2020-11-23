#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <iostream>
#include <cmath>
#include <utility>
#include "keyboard_reader.h"
#include "can_io.h"

class InputHandler{
public:
    InputHandler();
    ~InputHandler(){reader.stop();}//no need
    bool run(int cycleTime);
    KeyboardReader reader;
    CanInput data;
    CANIO canIO;
};

#endif // INPUTHANDLER_H