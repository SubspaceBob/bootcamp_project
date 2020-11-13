#include "engine.h"
#include "CanInput.h"

Engine::Engine()
{
   engSts = On;
   engTrq = 0;
}

void Engine::run(canInput inputVal, float EngineSpeed, int TimeStep){
   //std::cout << "running Engine\n";

   if(engSts == 0 && (int)inputVal.StartBtn == 1) {
      std::cout << "Starting engine" << std::endl;
      this->setEngSts(On);
      setEngTrqFromAccPdl(inputVal, EngineSpeed);
   }
   else if(engSts == 1 && (int)inputVal.StartBtn == 1) {
      std::cout << "Stopping engine" << std::endl;
      this->setEngSts(Off);
      this->engTrq = 0;
   }
   else if(engSts == 1) {
      setEngTrqFromAccPdl(inputVal, EngineSpeed);
   }


   // read AcclPdl value from CAN
   // read EngineRPS from gearbox(calculated in previous loop)
   // Calculate new Trq
}

void Engine::setEngTrqFromAccPdl(canInput inputVal, float EngineSpeed)
{
   if(inputVal.AccPdl)
   {
      engTrq = 300; // Pedal to the metal
      std::cout << "pedal to the metal" << std::endl;
      
   }
   else
   {
      engTrq = 0;
   }
   
}
