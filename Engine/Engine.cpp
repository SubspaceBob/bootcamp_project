#include "engine.h"
#include "CanInput.h"

 Engine::Engine()
 {
    engSts = On;
    engTrq = 0;
 }

 void Engine::run(canInput inputVal){
     //std::cout << "running Engine\n";
     if(this->getEngSts() == 0 && (int)inputVal.StartBtn == 1) {
       std::cout << "engineSts" << this->getEngSts() << "Set Trq 300" << std::endl;
       this->setEngSts(On);
       this->setEngTrq(300);
    }
    else if(this->getEngSts() == 1 && (int)inputVal.StartBtn == 1) {
       std::cout << "engineSts" << this->getEngSts() << "Set Trq 0" << std::endl;
       this->setEngSts(Off);
       this->setEngTrq(0);
    }
    /*else {
        std::cout << "Problem with engineSts: " << this->getEngSts() << std::endl;
       std::cout << "startBtn " << (int)inputVal.StartBtn << std::endl;
    }*/


     // read AcclPdl value from CAN
     // read EngineRPS from gearbox(calculated in previous loop)
     // Calculate new Trq
 }
