#ifndef GEARCLASS_H
#define GEARCLASS_H
#include <iostream> 
#include "can_io.h"
#include "com_eng_gbx_def.h"

namespace VEHICLE
{
    const static float WHEEL_RADIUS         = 0.3;
    const static uint16_t VEHICLE_MASS      = 1500;
    const static int MAX_BRAKETORQUE        = 20000;   // A bit magic, should be roughly twice as strong as max engine torque, needs update when gear ration changes... 
    const static float GEARRATIOS[8]        = {5.25, 3.029, 1.950, 1.457,1.221, 1.000, 0.809, 0.673};
    const static float REVERSE_GEARRATIO    = 4.015;
    const static float FINALGEAR            = 3.075;
    const static float ENGINE_IDLE_RPS      = 12;
    const static float TOPSPEED_KPH         = 255;
    const static float MAX_ENGINETORQUE     = 450;
    const static float ROLLINGRESISTANCE    = MAX_ENGINETORQUE * FINALGEAR * GEARRATIOS[0] * WHEEL_RADIUS * 3.6 / (VEHICLE_MASS * TOPSPEED_KPH);    // Magic number = 255km/h topspeed /60 * FinalGear * TopGear * WheelRadius / VEHICLE_MASS
}

class Gearbox
{
    float vhlSpeed; // 0-70,8 m/s
    float engineRPS; // 0-10000 rpm
    float gearboxRPS;
    int8_t engagedGear;  //what gear we are in while in D 
    GearPattern gearStickPosition;  //Active gear (P,R,N,D)
    Trq calculateBrakeTorque(int8_t brakePdl);
    void setGearStick( int8_t gearStickRequest, int8_t brakePedal);
    float calculateEngineRPS(float gearbox_rps, float currentGearRatio, EngSts engSts);
    float getGearRatio(float engineSpeed, GearPattern gearStick);
    
    public:
    Gearbox();
    ~Gearbox()=default;
    float getSpeed();
    float getRPS();
    GearPattern getGearStick();
    int8_t getEngagedGear();
    void run(CanInput &input, CanOutput &canOut, Trq engTrq, EngSts engSts, int timeStep);
};

#endif