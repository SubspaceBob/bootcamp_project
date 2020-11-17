#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include "can_io.h"
enum EngSts : uint8_t {Off, On};
typedef uint16_t Trq;
namespace VEHICLE
{
    const static float MAX_TORQUE         = 450;
    const static float IDLE_TORQUE        = 20;
}

class Engine{
    public:
        // Engine has On/Off status and generates a torque based on AccPdl from CanInput
        // and current EngineSpeed from gearbox. run method is its main method.
        Engine();
        ~Engine()= default;
        void run(CanInput inputVal, CanOutput CANOut, float engineSpeed, int timeStep, int gearStick);
        
        // Getters
        EngSts getEngSts(){return engSts;}
        Trq getEngTrq(){return engTrq;}

    private:
        EngSts engSts;
        Trq engTrq;
        CanInput lastCycle;

        // Setters
        void setEngTrqFromAccPdl(CanInput inputVal, float engineSpeed);//Chosen maxTrq = 300
        
};
#endif
