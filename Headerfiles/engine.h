#ifndef engine_h
#define engine_h
#include <iostream>
#include "CanInput.h"
enum EngSts : uint8_t {Off, On};
typedef uint16_t Trq;

class Engine{
    public:
        // TODO: Constructor values are stubbed to always on acc to 1st story of 
        // Start Engine Epic, change to proper init values once we have logics.
        Engine();
        ~Engine()= default;

    
        void run(canInput inputVal, float EngineSpeed, int TimeStep);
        // Getters
        EngSts getEngSts(){return engSts;}
        uint16_t getEngTrq(){return engTrq;}

    private:
        EngSts engSts   = Off;
        Trq engTrq      = 0;
        // Setters
        void setEngSts(EngSts engSts){this->engSts = engSts;}
                
        //Chosen maxTrq = 300
        void setEngTrqFromAccPdl(canInput inputVal, float EngineSpeed);

};
#endif
