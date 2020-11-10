#include <iostream>
#include "ReadCan/CanInput.h"
#include "Engine/engine.h"
#include "Gearbox/GearClass.h"
#include "SendCan/frameToBus.h"
#include "Includes/socketcan_cpp/socketcan_cpp.h"

bool canReader(canInput &out); 
void FramePacker(Engine &EngingeOut, Gear &GearboxOut);

int main()
{
    canInput inputVal;
    Engine Engine;
    Gear Gearbox;
    bool error=false;
    while(true)
    {
    error=canReader(inputVal);
    FramePacker(Engine, Gearbox);
    if (error==true)
        {break;}

    }
}