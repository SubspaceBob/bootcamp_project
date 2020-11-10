#ifndef engine_h
#define engine_h
#include <iostream>

enum EngSts : uint8_t {Off, On};

class Engine{
    public:
        // TODO: Constructor values are stubbed to always on acc to 1st story of 
        // Start Engine Epic, change to proper init values once we have logics.
        Engine() = default;
        ~Engine()= default;

        // Setters
        void setEngSts(EngSts engSts){this->engSts = engSts;}
        //Chosen maxTrq = 300
        void setEngTrq(uint16_t engTrq){if(engTrq <=300)this->engTrq = engTrq;}

        void run();
        // Getters
        EngSts getEngSts(){return engSts;}
        uint16_t getEngTrq(){return engTrq;}

    private:
        EngSts engSts;
        uint16_t engTrq;
        
};
#endif
