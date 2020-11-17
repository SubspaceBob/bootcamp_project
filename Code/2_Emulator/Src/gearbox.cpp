#include "gearbox.h"
#include "can_io.h"
#include "engine.h"


Gearbox::Gearbox()
{
vhlSpeed        = 0; // 0-70,8 m/s
engineRPS       = 0; // 0-10000 rpm
gearboxRPS      = 0;
engagedGear     = 0;  //what gear we are in while in D 
gearStickPosition=GearPattern::P;
}

float Gearbox::getSpeed()
{
    return (vhlSpeed);
}

float Gearbox::getRPS()
{
    return (engineRPS);
}

GearPattern Gearbox::getGearStick()
{
    return (gearStickPosition);
}

int8_t Gearbox::getEngagedGear()
{
    return (engagedGear);
}

float Gearbox::calculateEngineRPS(float gearbox_rps, int8_t engaged_gear)
{
    float engine_rps = gearbox_rps * VEHICLE::GEARRATIOS[engaged_gear] * VEHICLE::FINALGEAR;
    return std::max<float>(engine_rps, VEHICLE::ENGINE_IDLE_RPS); // Engine does not go below IDLE_RPS
}

void Gearbox::setGearStick(int8_t gearStickRequest, int8_t brakePedal)
{
    // If GearStickRequest 0-3, low vehicle speed and brakepedal somewhat pressed
    if (0<=gearStickRequest && gearStickRequest<4 && vhlSpeed<1 && brakePedal > 5)
    {
        if (gearStickRequest==0)
        {
            gearStickPosition=GearPattern::P;
        }
        else if (gearStickRequest==1)
        {
            gearStickPosition=GearPattern::R;
        }
        else if (gearStickRequest==2)
        {
            gearStickPosition=GearPattern::N;
        }
        else if (gearStickRequest==3)
        {
            gearStickPosition=GearPattern::D;
        }
    }
}

void Gearbox::setEngagedGear(float engineSpeed)
{
    // Very simple shift up/down based on Engine RPM
    if (engineSpeed > (3500/60) && engagedGear <7)
    {
        engagedGear++;
    }
    else if (engineSpeed < (1000/60) && engagedGear > 0)
    {
        engagedGear--;
    }
    // Sets the engagedGear index, the ratio is given by GEARRATIOS[engagedGear]
}

Trq Gearbox::calculateBrakeTorque(int8_t brakePdl)
{
    // Calculates Brake Torque based on BrakePedal Value and max possible brake torque.
    // BrakePdl is 0-100, BrakePdl == 100 -> BrkTrq = MAX_BRAKETORQUE
    Trq BrkTrq = VEHICLE::MAX_BRAKETORQUE * brakePdl / 100;
}

void Gearbox::run(CanInput &input, CanOutput &canOut, Trq engTrq, int timeStep){
    /*
    Basic physics/mechanics:
    Torque from engine is used to calculate the vehicle acceleration, which is integrated into vehicle speed.

    Acceleration = WheelTorque                           *WheelRadius /VehicleMass - RollingResistance
                 = (EngineTorque*GearRatio - BrakeTorque)*WheelRadius /VehicleMass - VehicleSpeed*MagicNumber 
    
    VehicleSpeed = VehicleSpeed + DeltaSpeed
                 = VehicleSpeed + Acceleration*timeStep

    GearboxRPS   = VehicleSpeed / WheelRadius

    EngineRPS    = GearboxRPS * GearRatio * FinalGear 
    EngineRPS is used as input to Engine to calculate torque next iteration.
    */

    //
    this->setGearStick(input.gearReq, input.brkPdl);
    this->setEngagedGear(engineRPS);

    // Get EngineTorque and check against GearStickPosition
    Trq engine_torque = 0;
    if (gearStickPosition == GearPattern::D)
    {
        engine_torque = engTrq;
    }

    // Calculate brake torque and rolling resistance
    Trq BrakeTrq = calculateBrakeTorque(input.brkPdl);
    auto RollingResistance = vhlSpeed * vhlSpeed * VEHICLE::ROLLINGRESISTANCE; //Exponential

    auto acceleration   = (engine_torque * VEHICLE::GEARRATIOS[engagedGear] * VEHICLE::FINALGEAR - BrakeTrq) * VEHICLE::WHEEL_RADIUS /VEHICLE::VEHICLE_MASS - RollingResistance;
    vhlSpeed        = vhlSpeed + acceleration * timeStep * 0.001; //TimeStep is Int Milliseconds, convert to Seconds
    
    // If only rolling resistance is slowing down, it never stops.
    // Low speed and deceleration can be rounded of to stopped. 
    if (vhlSpeed < 0.1 && acceleration < 0)
    {
        vhlSpeed = 0;
    }
    
    // We don't allow negative speed, and then the acceleration should also be forced to zero.
    // TODO: This limit should be applied on the EngineRPS and take GearStickPosition into consideration, 
    // and braketorque to take driving direction into consideration. But it makes a bit more complicated.
    if (vhlSpeed < 0) 
    {
        acceleration = 0;
        vhlSpeed = 0;
    }

    // VehicleSpeed[m/s] = GearboxRPS[rev/s] * WheelRadius[m] * 2*Pi
    gearboxRPS  = vhlSpeed /(VEHICLE::WHEEL_RADIUS * 2 * 3.1416);
    engineRPS   = calculateEngineRPS(gearboxRPS, engagedGear);

    // Store values to CANOut
    canOut.gearStick    = static_cast<uint8_t> (gearStickPosition);
    canOut.RPM          = static_cast<uint16_t>(engineRPS * 60);
    canOut.vhlSpeed     = static_cast<uint8_t> (vhlSpeed * 3.6);
    
    std::cout <<" EngTrq: "             << engTrq               << 
                " Engaged Gear: "       << static_cast<int> (engagedGear)          << 
                " GearStickPosition: "  << static_cast<int> (gearStickPosition)  << 
                " Acceleration: "       << acceleration         << 
                " VehicleSpeed[km/h]: " << vhlSpeed * 3.6       << 

                //" RollingResistance : " << RollingResistance  <<
                std::endl; 
}
