#include "GearClass.h"
#include "CanInput.h"
#include "engine.h"


 Gearbox::Gearbox()
 {
    this->VehicleSpeed=0;
    this->EngineRPS=0;
    this->GearStickPosition=GearPattern::D;
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

void Gearbox::setSpeed(uint16_t x)
{
    float y=x*0.236; // x/300*0.708*100
    this->VehicleSpeed=y;
}

void Gearbox::setRPS(uint16_t x)
{
    float y=x*0.556; // x/300*1.667*100
    this->EngineRPS=y;
}

void Gearbox::setGearStick(int8_t x)
{
    if (0<=x && x<4 && this->VehicleSpeed==0)
    
    {if (x==0)
    {this->GearStickPosition=GearPattern::P;} //this->GearStickPosition=static_cast<GearPattern>(x)/*P*/;
    
    else if (x==1)
    {this->GearStickPosition=GearPattern::R;}
    
    else if (x==2)
    {this->GearStickPosition=GearPattern::N;}
    
    else if (x==3)
    {this->GearStickPosition=GearPattern::D;}
    }
}

void Gearbox::setEngagedGear()
{
    this->EngagedGear=0;
}

void Gearbox::run(canInput &Input, Engine &Eng){
    this->setGearStick(Input.GearReq);
    this->setSpeed(Eng.getEngTrq());
    this->setRPS(Eng.getEngTrq());
    this->setEngagedGear();
}
