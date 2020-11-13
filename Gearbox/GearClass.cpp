#include "GearClass.h"
#include "CanInput.h"
#include "engine.h"


 Gearbox::Gearbox()
 {
    VehicleMass     = 2000; 
    WheelRadius     = 0.3;
    VehicleSpeed    = 0; // 0-70,8 m/s
    EngineRPS       = 0; // 0-10000 rpm
    GearboxRPS      = 0;
    //GearRatios[4]      = {1, 1 ,1, 1}; // Defined in Header
    FinalGear       = 4;
    EngagedGear     = 0;  //what gear we are in while in D 
    GearStickPosition=GearPattern::D;
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
    std::cout << "setSpeed: "<< std::endl << std::flush;
}

void Gearbox::setRPS(uint16_t x)
{
    float y=x*0.556; // x/300*1.667*100
    this->EngineRPS=y;
    std::cout << "setRPS: "<< std::endl << std::flush;
}

void Gearbox::setGearStick(int8_t x)
{
    if (0<=x && x<4 && this->VehicleSpeed<1)
    //std::cout << "setGearStick: "<< std::endl << std::flush;
    {if (x==0)
    {this->GearStickPosition=GearPattern::P;
    std::cout << "Gear in P: "<< std::endl << std::flush;} //this->GearStickPosition=static_cast<GearPattern>(x)/*P*/;
    
    else if (x==1)
    {this->GearStickPosition=GearPattern::R;
    std::cout << "Gear in R: "<< std::endl << std::flush;}
    
    else if (x==2)
    {this->GearStickPosition=GearPattern::N;
    std::cout << "Gear in N: "<< std::endl << std::flush;}
    
    else if (x==3)
    {this->GearStickPosition=GearPattern::D;
    std::cout << "Gear in D: "<< std::endl << std::flush;}
    }
}

void Gearbox::setEngagedGear()
{
    this->EngagedGear=0;
    // std::cout << "setEngagedGear: "<< std::endl << std::flush;
}

void Gearbox::run(canInput &Input, Trq EngTrq, int TimeStep){
    /*
    GearStickPosition = setGearStickPosition
    EngagedGear = setEngagedGear(WheelSpeed, EngineSpeed, GearStickPosition)

    GearRatio    = GearRation[EngagedGear]

    Acceleration = WheelTorque                           *WheelRadius /VehicleMass - RollingResistance
                 = (EngineTorque*GearRatio - BrakeTorque)*WheelRadius /VehicleMass - VehicleSpeed*MagicNumber 
    
    VehicleSpeed = VehicleSpeed + DeltaSpeed = VehicleSpeed + Acc*DeltaTime
    GearboxRPS   = VehicleSpeed / WheelRadius
    EngineRPS    = GearboxRPS / GearRatio 
    */

    this->setGearStick(Input.GearReq);
    this->setEngagedGear();
    // TODO add BrakeTorque and Rolling Resistance to acceleration
    auto acceleration   = EngTrq * GearRatios[EngagedGear] * FinalGear *WheelRadius /VehicleMass;
    VehicleSpeed        = VehicleSpeed + acceleration * TimeStep * 0.001; //TimeStep is Int Milliseconds, convert to Seconds

    GearboxRPS  = VehicleSpeed/WheelRadius;
    EngineRPS   = GearboxRPS/GearRatios[EngagedGear];

    std::cout << "EngTrq: "<< EngTrq << " Acceleration: " << acceleration << " VehicleSpeed[km/h]: " << VehicleSpeed*3.6 << std::endl;
    //std::cout << "Vehicle Speed : " << VehicleSpeed << std::endl;

    // this->setSpeed(Eng.getEngTrq());
    // this->setRPS(Eng.getEngTrq());
}
