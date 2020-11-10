#include "engine.h"

 Engine::Engine()
 {
    engSts = On;
    engTrq = 0;
 }

 void Engine::run(){
     std::cout << "running Engine\n";
     // read AcclPdl value from CAN
     // read EngineRPS from gearbox(calculated in previous loop)
     // Calculate new Trq
 }