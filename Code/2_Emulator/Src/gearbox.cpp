#include "gearbox.h"
#include "can_io.h"

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

float calculateEngineRPS(const float &gearbox_rps, const float &currentGearRatio, const EngSts &engSts)
{
    float engine_rps = gearbox_rps * currentGearRatio;
    if (engSts)
    {
        return std::max<float>(engine_rps, VEHICLE::ENGINE_IDLE_RPS); // Engine does not go below IDLE_RPS
    }
    else
    {
        return 0;
    }
}

void Gearbox::setGearStick(const int8_t &gearStickRequest, const int8_t &brakePedal)
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
        else if (gearStickRequest==4) {} //No request = ignore
        else { // If this then something seriously wrong
            std::cout <<"Major fail in gearStickselect" <<std::endl;
        }
    }
}
void Gearbox::gearShiftLogic()
{
    // Gear Shift logic, updating engagedGear depending on enginespeed and gearStick
    if (gearStickPosition==GearPattern::D)
    {
        // Very simple shift up/down based on Engine RPM, sets the engagedGear index, the ratio is given by GEARRATIOS[engagedGear]
        if (engineRPS > (6000/60) && engagedGear <7)
        {
            engagedGear++;
        }
        else if (engineRPS < (2000/60) && engagedGear > 0)
        {
            engagedGear--;
        }
    }
    // Would it be better to return engagedGear?
}

float calculateGearRatio(const GearPattern &gearStick, const int8_t &engagedGear)
{
    // Since method is not attached to class, the method should have some limit on input, for testing it.
    // A bit weird since the limit should be on the function setting the gear.
    auto gear = std::max<int8_t>(std::min<int8_t>(engagedGear,
                                                    7),
                                                    0);

    if (gearStick==GearPattern::D)
    {
        return VEHICLE::GEARRATIOS[gear] * VEHICLE::FINALGEAR;
    }
    else if (gearStick==GearPattern::R)
    {
        return VEHICLE::REVERSE_GEARRATIO * VEHICLE::FINALGEAR;
    }
    else
    {
        return 0;
    } 
}

Trq Gearbox::calculateBrakeTorque(const int8_t &brakePdl)
{
    // Calculates Brake Torque linearly based on BrakePedal Value and max possible brake torque.
    // Limit on brakepedal input and on braketorque output, a bit overkill but maybe good practice
    auto brake_pedal = std::max<float>(std::min<float>(brakePdl, 
                                                        100),    // Range top limiter
                                                        0);      // Range bottom limiter
    
    // Linear scale
    auto brake_torque = VEHICLE::MAX_BRAKETORQUE * brake_pedal / 100;

    Trq BrkTrq = std::max<float>(std::min<float>(brake_torque, 
                                        VEHICLE::MAX_BRAKETORQUE), // Range top limiter
                                        0);                        // Range bottom limiter
}

void Gearbox::run(CanInput &input, CanOutput &canOut, Trq engTrq, EngSts engSts, int timeStep){
    /*
    Basic physics/mechanics:
    Torque from engine is used to calculate the vehicle acceleration, which is integrated into vehicle speed.
    WheelTorque  = EngineTorque * GearRatio - BrakeTorque

    Acceleration = WheelTorque                           *WheelRadius /VehicleMass - RollingResistance
                 = (EngineTorque*GearRatio - BrakeTorque)*WheelRadius /VehicleMass - VehicleSpeed*MagicNumber 
    
    VehicleSpeed = VehicleSpeed + DeltaSpeed
                 = VehicleSpeed + Acceleration*timeStep

    GearboxRPS   = VehicleSpeed / WheelRadius

    EngineRPS    = GearboxRPS * GearRatio
    EngineRPS is used as input to Engine to calculate torque next iteration.
    */

      // Evaluate gearStick position
    setGearStick(input.gearReq, input.brkPdl);

    // Evaluate gearShifting
    gearShiftLogic();
    
    // calculate gear ratio depending on GearStickPosition and EngagedGear(used if Drive)
    float currentGearRatio = calculateGearRatio(gearStickPosition, engagedGear);

    // Gearbox should use the engine torque only if in D or R, else the torque is 0.
    Trq engine_torque = 0;
    if (gearStickPosition == GearPattern::D || gearStickPosition == GearPattern::R)
    {
        engine_torque = engTrq * 2; // TorqueConverter to double torque output
    }

    // Calculate brake torque and rolling resistance
    Trq BrakeTrq = calculateBrakeTorque(input.brkPdl);
    auto RollingResistance = vhlSpeed * VEHICLE::ROLLINGRESISTANCE; //Exponential

    // Calculate acceleration and vehicle speed
    auto acceleration   = (engine_torque * currentGearRatio - BrakeTrq) * VEHICLE::WHEEL_RADIUS /VEHICLE::VEHICLE_MASS - RollingResistance;
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
    engineRPS   = calculateEngineRPS(gearboxRPS, currentGearRatio, engSts);

    // Store values to CANOut
    canOut.gearStick    = static_cast<uint8_t> (gearStickPosition);
    canOut.RPM          = static_cast<uint16_t>(engineRPS * 60);
    canOut.vhlSpeed     = static_cast<uint8_t> (vhlSpeed * 3.6);
    canOut.engagedGear  = static_cast<uint8_t> (engagedGear);
    
    std::cout <<//" EngTrq: "             << engTrq                                   << 
                //" Engaged Gear: "       << static_cast<int> (engagedGear)           << 
                //" GearStickPosition: "  << static_cast<int> (gearStickPosition)     << 
                " GearRatio: "          << currentGearRatio                         << 
                " RollingResistance: "  << RollingResistance                        << 
                " Acceleration: "       << acceleration                             << 
                " VehicleSpeed[km/h]: " << vhlSpeed * 3.6                           << 

                //" RollingResistance : " << RollingResistance  <<
                std::endl; 
}
