#include<iostream> 
enum GearPattern :int8_t
{
    P, R, N, D
};


class Gear
{
    float speed; // 0-70,8 m/s 
    float RPS; // 0-10000 rpm
    GearPattern GearStick;  //Active gear (P,R,N,D)
    int8_t EngagedGear;  //what gear we are in while in D 

    public:
    Gear();
    ~Gear()=default;
    float getSpeed();
    float getRPS();
    GearPattern getGearStick();
    int8_t getEngagedGear();
    void setSpeed(float x);
    void setRPS(float x);
    void setGearStick( GearPattern x);
    void setEngagedGear(int8_t x);
};
