#include<iostream> 
enum GearPattern :int8_t
{
    P, R, N, D
};


class Gear
{
    float speed; // 0-70,8 m/s 
    float RPS; // 0-10000 rpm
    GearPattern ActiveGear;  //Active gear (P,R,N,D)
    int8_t GearInD;  //what gear we are in while in D 

    public:
    Gear();
    ~Gear()=default;
    int8_t getSpeed();
    int16_t getRPS();
    GearPattern getActiveGear();
    int8_t getGearInD();
    void setSpeed();
    void setRPS();
    void setActiveGear();
    void setGearInD();
};
