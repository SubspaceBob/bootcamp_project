#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include "can_io.h"
#include "com_eng_gbx_def.h"

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
        void run(CanInput &inputVal, CanOutput &CANOut, float engineSpeed, int timeStep, int gearStick);
        
        // Getters
        inline EngSts getEngSts();
        inline Trq getEngTrq(){return engTrq;}

    private:
        EngSts engSts;
        Trq engTrq;
        CanInput lastCycle;

        // Setters
        //Chosen maxTrq = 450
        void setEngTrqFromAccPdl(CanInput inputVal, float engineSpeed);
};

inline EngSts Engine::getEngSts() {return engSts;}

#endif
