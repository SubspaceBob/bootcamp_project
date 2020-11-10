#include "GearClass.h"

 Gearbox::Gearbox()
 {
    this->VehicleSpeed=0;
    this->EngineRPS=0;
    this->GearStickPosition=D;
    this->EngagedGear=0;
 }
float Gearbox::getSpeed()
{
    return (this->VehicleSpeed);
}

float Gearbox::getRPS()
{
    return (this->EngineRPS);
}

GearPattern Gearbox::getGearStick()
{
    return (this->GearStickPosition);
}

int8_t Gearbox::getEngagedGear()
{
    return (this->EngagedGear);
}

void Gearbox::setSpeed(float x)
{
    this->VehicleSpeed=x;
}

void Gearbox::setRPS(float x)
{
    this->EngineRPS=x;
}

void Gearbox::setGearStick(GearPattern x)
{
    this->GearStickPosition=x;
}

void Gearbox::setEngagedGear(int8_t x)
{
    this->EngagedGear=x;
}

void run(){
    std::cout << "running gearbox\n";
    // Read Trq from Engine
    // Read GearStickRequest, BrkPdl from CAN
    // FUTURE: calculate new EngagedGear (ratio)
    // Calculate new vehicle speed given the current VehicleSpeed, SimulationStepSize and CANInput(GearStuff and BrkPdl) and Engine.
    // Calculate new EngineRPS given the the new VehicleSpeed, EngagedGear
}
