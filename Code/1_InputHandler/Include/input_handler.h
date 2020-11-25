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
    bool run();
    KeyboardReader reader;
    void writeToCan();
    //Frame1 frame1; // StartBtn, QuitEmul & Battery telltale
    //Frame2 frame2; // Hazard, blinkers & high_beam telltale
    //Frame3 frame3; // BrkPdl, AccPdl, hand_brake & ABS telltale
    //Frame4 frame4; // GearReq, seat_belts, door_open telltale
    CANIO canIO;
};

#endif // INPUTHANDLER_H