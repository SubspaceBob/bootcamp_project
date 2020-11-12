#include <iostream>
#include "frameToBus.h"
#include "engine.h"
#include "GearClass.h"


void FramePacker(Engine &EngingeOut, Gearbox &GearboxOut)
{
    frameToBus(004, GearboxOut.getSpeed());
    frameToBus(005, static_cast <int8_t> (GearboxOut.getGearStick()));
};
