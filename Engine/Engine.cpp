#include "engine.h"
#include "CanInput.h"

Engine::Engine()
{
   engSts = Off;
   engTrq = 0;
}

void Engine::run(canInput inputVal, float EngineSpeed, int TimeStep){
   //std::cout << "running Engine\n";

   // Using last cycle to make sure I only react once to each buttonpress
   if(engSts == 0 && (int)inputVal.StartBtn == 1 && lastCycle.StartBtn == 0) {
      // Engine off and first press = Turn on
      std::cout << "Starting engine" << std::endl;
      this->setEngSts(On);
      lastCycle.StartBtn = 1;
   }
   else if(engSts == 1 && (int)inputVal.StartBtn == 1 && lastCycle.StartBtn == 0) {
         // Engine on and first press = Trun off
         std::cout << "Stopping engine" << std::endl;
         this->setEngSts(Off);
         lastCycle.StartBtn = 1;
   }
   else if ((int)inputVal.StartBtn == 1) {
      // Not first press - just wait for release
      lastCycle.StartBtn = 1;
   }
   else if ((int)inputVal.StartBtn == 0)
   {
      // Button released reset last cycle to 
      // be ready for another press
      lastCycle.StartBtn = 0;
   }
   else {
      // If this happens my logic is in Friday afternoon mode...
      std::cout << "Major fail in Engine On/Off" << std::endl;
      exit(EXIT_FAILURE);
   }
   
   setEngTrqFromAccPdl(inputVal, EngineSpeed);
}

void Engine::setEngTrqFromAccPdl(canInput inputVal, float EngineSpeed)
{
   // read AcclPdl value from CAN
   // read EngineRPS from gearbox(calculated in previous loop)
   // Calculate new Trq
   if(inputVal.AccPdl && this->engSts== On)
   {
      engTrq = 300; // Pedal to the metal
      std::cout << "pedal to the metal" << std::endl;
      
   }
   else
   {
      engTrq = 0;
   }
   
}