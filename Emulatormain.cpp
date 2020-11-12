#include <iostream>
#include "CanInput.h"
#include "engine.h"
#include "GearClass.h"
#include "frameToBus.h"
#include <thread>

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
    Engine.run(inputVal);
    Gearbox.run(inputVal, Engine);
    FramePacker(Engine, Gearbox);
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    if (error==true)
        {break;}
    /*printf("%d ", inputVal.GearReq);
    printf("%d ", inputVal.AccPdl);
    printf("%d \n", inputVal.BrakePdl);*/
    }
}