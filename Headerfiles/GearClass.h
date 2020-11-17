#ifndef GEARCLASS_H
#define GEARCLASS_H
#include<iostream> 
#include "CanInput.h"
#include "engine.h"

const static float WHEEL_RADIUS      = 0.3;
const static uint16_t VEHICLE_MASS   = 2000;
const static int MAX_BRAKETORQUE     = 20000;   // A bit magic, should be roughly twice as strong as max engine torque, needs update when gear ration changes... 
const static float ROLLINGRESISTANCE = 0.02;    // Magic number from tuning

enum class GearPattern :int8_t
{
    P, R, N, D
};

class Gearbox
{
    float VehicleSpeed; // 0-70,8 m/s
    float EngineRPS; // 0-10000 rpm
    float GearboxRPS;
    float GearRatios[4] = {4, 4, 4, 4};
    float FinalGear;
    int8_t EngagedGear;  //what gear we are in while in D 
    GearPattern GearStickPosition;  //Active gear (P,R,N,D)
    Trq CalculateBrakeTorque(int8_t BrakePdl);

    public:
    Gearbox();
    ~Gearbox()=default;
    float getSpeed();
    float getRPS();
    GearPattern getGearStick();
    int8_t getEngagedGear();
    void setSpeed(uint16_t x);
    void setRPS(uint16_t x);
    void setGearStick( int8_t x);
    void setEngagedGear();
    void run(canInput &Input, canOutput &CANOut, Trq EngTrq, int TimeStep);
};

#endif