#include <iostream>
#include "frameToBus.h"

void FramePacker(Engine &EngingeOut, Gear &GearboxOut)
{
    frameToBus(004, GearboxOut.getSpeed());
    frameToBus(005, GearboxOut.getGearStick());
};
