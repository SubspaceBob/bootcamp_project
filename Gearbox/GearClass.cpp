#include "GearClass.h"

 Gear::Gear()
 {
    this->speed=0;
    this->RPS=0;
    this->GearStick=D;
    this->EngagedGear=0;
 }
float Gear::getSpeed()
{
    return (this->speed);
}

float Gear::getRPS()
{
    return (this->RPS);
}

GearPattern Gear::getGearStick()
{
    return (this->GearStick);
}

int8_t Gear::getEngagedGear()
{
    return (this->EngagedGear);
}

void Gear::setSpeed(float x)
{
    this->speed=x;
}

void Gear::setRPS(float x)
{
    this->RPS=x;
}

void Gear::setGearStick(GearPattern x)
{
    this->GearStick=x;
}

void Gear::setEngagedGear(int8_t x)
{
    this->EngagedGear=x;
}