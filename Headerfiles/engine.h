#ifndef engine_h
#define engine_h
#include <iostream>
#include "CanInput.h"
enum EngSts : uint8_t {Off, On};
typedef uint16_t Trq;

class Engine{
    public:
        // Engine has On/Off status and generates a torque based on AccPdl from CANInput
        // and current EngineSpeed from gearbox. run method is its main method.
        Engine();
        ~Engine()= default;
        void run(canInput inputVal, canOutput CANOut, float EngineSpeed, int TimeStep);
        
        // Getters
        EngSts getEngSts(){return engSts;}
        Trq getEngTrq(){return engTrq;}

    private:
        EngSts engSts;
        Trq engTrq;        
        //Chosen maxTrq = 300
        void setEngTrqFromAccPdl(canInput inputVal, float EngineSpeed);

};
#endif
