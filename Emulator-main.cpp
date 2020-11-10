#include <iostream>
#include "CanInput.h"
#include "engine.h"
#include "GearClass.h"
#include "frameToBus.h"

bool canReader(canInput &out); 
void FramePacker(Engine &EngingeOut, Gearbox &GearboxOut);

int main()
{
    canInput inputVal;
    Engine Engine;
    Gearbox Gearbox;
    bool error=false;

    while(true)
    {
    error=canReader(inputVal);
    Engine.run();
    Gearbox.run();
    FramePacker(Engine, Gearbox);
    if (error==true)
        {break;}

    }
}