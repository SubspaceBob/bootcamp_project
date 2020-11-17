#include "GearClass.h"
#include "CanInput.h"
#include "engine.h"


 Gearbox::Gearbox()
 {
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
    //std::cout << "setSpeed: "<< std::endl << std::flush;
}

void Gearbox::setRPS(uint16_t x)
{
    float y=x*0.556; // x/300*1.667*100
    this->EngineRPS=y;
    //std::cout << "setRPS: "<< std::endl << std::flush;
}

void Gearbox::setGearStick(int8_t GearStickRequest, int8_t BrakePedal)
{
    // If GearStickRequest 0-3, low vehicle speed and brakepedal somewhat pressed
    if (0<=GearStickRequest && GearStickRequest<4 && VehicleSpeed<1 && BrakePedal > 5)
    {
        if (GearStickRequest==0)
        {
            GearStickPosition=GearPattern::P;
        }
        else if (GearStickRequest==1)
        {
            GearStickPosition=GearPattern::R;
        }
        else if (GearStickRequest==2)
        {
            GearStickPosition=GearPattern::N;
        }
        else if (GearStickRequest==3)
        {
            GearStickPosition=GearPattern::D;
        }
    }
}

void Gearbox::setEngagedGear()
{
    // Sets the EngagedGear index, the ratio is given by GearRatio[EngagedGear]
    this->EngagedGear=0;
}

Trq Gearbox::CalculateBrakeTorque(int8_t BrakePdl)
{
    // Calculates Brake Torque based on BrakePedal Value and max possible brake torque.
    // BrakePdl is 0-255, BrakePdl == 255 -> BrkTrq = MAX_BRAKETORQUE
    // TODO: If driving in reverse the Torque should be negated.
    Trq BrkTrq = MAX_BRAKETORQUE * BrakePdl / 255;
}

void Gearbox::run(canInput &Input, canOutput &CANOut, Trq EngTrq, int TimeStep){
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

    this->setGearStick(Input.GearReq, Input.BrakePdl);
    this->setEngagedGear();

    // Get EngineTorque and check against GearStickPosition
    Trq engine_torque = 0;
    if (GearStickPosition == GearPattern::D)
    {
        engine_torque = EngTrq;
    }

    // Calculate brake torque and rolling resistance
    Trq BrakeTrq = CalculateBrakeTorque(Input.BrakePdl);
    auto RollingResistance = VehicleSpeed * ROLLINGRESISTANCE;

    auto acceleration   = (engine_torque * GearRatios[EngagedGear] * FinalGear - BrakeTrq) * WHEEL_RADIUS /VEHICLE_MASS - VehicleSpeed * ROLLINGRESISTANCE;
    VehicleSpeed        = VehicleSpeed + acceleration * TimeStep * 0.001; //TimeStep is Int Milliseconds, convert to Seconds
    
    // If only rolling resistance is slowing down, it never stops.
    // Low speed and deceleration can be rounded of to stopped. 
    if (VehicleSpeed < 0.1 && acceleration < 0)
    {
        VehicleSpeed = 0;
    }
    
    // We don't allow negative speed, and then the acceleration should also be forced to zero.
    // TODO: This limit should be applied on the EngineRPS and take GearStickPosition into consideration, 
    // and braketorque to take driving direction into consideration. But it makes a bit more complicated.
    if (VehicleSpeed < 0) 
    {
        acceleration = 0;
        VehicleSpeed = 0;
    }

    GearboxRPS  = VehicleSpeed/WHEEL_RADIUS;
    EngineRPS   = GearboxRPS/GearRatios[EngagedGear];

    // Store values to CANOut
    CANOut.GearStickPos     = static_cast<uint8_t> (GearStickPosition);
    CANOut.RPM              = static_cast<uint16_t>(EngineRPS*60);
    CANOut.VehicleSpeed     = static_cast<uint8_t> (VehicleSpeed*3.6);
    
    std::cout <<" EngTrq: "             << EngTrq               << 
                " GearStickPosition: "  << static_cast<int> (GearStickPosition)               << 
                " Acceleration: "       << acceleration         << 
                " VehicleSpeed[km/h]: " << VehicleSpeed*3.6     << 

                //" RollingResistance : " << VehicleSpeed * ROLLINGRESISTANCE <<
                std::endl;
 
    // this->setSpeed(Eng.getEngTrq());
    // this->setRPS(Eng.getEngTrq());
}
