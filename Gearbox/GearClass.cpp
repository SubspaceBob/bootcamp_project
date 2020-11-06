#include "GearClass.h"

 Gear::Gear()
 {
    this->speed=0;
    this->RPS=0;
    this->ActiveGear=D;
    this->GearInD=0;
 }
int8_t Gear::getSpeed()
{
    return (this->speed);
}

int16_t Gear::getRPS()
{
    return (this->RPS);
}

GearPattern Gear::getActiveGear()
{
    return (this->ActiveGear);
}

int8_t Gear::getGearInD()
{
    return (this->GearInD);
}

void Gear::setSpeed()
{
    this->speed=0;
}

void Gear::setRPS()
{
    this->RPS=0;
}

void Gear::setActiveGear()
{
    this->ActiveGear=P;
}

void Gear::setGearInD()
{
    this->GearInD=0;
}