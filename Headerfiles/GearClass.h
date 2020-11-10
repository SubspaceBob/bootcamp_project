#include<iostream> 
enum GearPattern :int8_t
{
    P, R, N, D
};

class Gearbox
{
    int VehicleMass = 2000; 
    float WheelRadius = 0.3;
    float VehicleSpeed; // 0-70,8 m/s 
    float EngineRPS; // 0-10000 rpm
    GearPattern GearStickPosition;  //Active gear (P,R,N,D)
    int8_t EngagedGear;  //what gear we are in while in D 

    public:
    Gearbox();
    ~Gearbox()=default;
    float getSpeed();
    float getRPS();
    GearPattern getGearStick();
    int8_t getEngagedGear();
    void setSpeed(float x);
    void setRPS(float x);
    void setGearStick( GearPattern x);
    void setEngagedGear(int8_t x);
    void run();
};
