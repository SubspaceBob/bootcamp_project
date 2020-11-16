#include "engine.h"
#include "CanInput.h"

Engine::Engine()
{
   // Init values are no torque but engine is started, for now
   engSts = On;
   engTrq = 0;
}

void Engine::run(canInput inputVal, canOutput CANOut, float EngineSpeed, int TimeStep)
{
   // Move Stop/Start code to separate function?
   // Make sure to have a slow stop and start procedure(>200ms?) to not trigger this 
   // multiple times on one keypress, memory is read more(10ms cycle) often than CAN
   // is sent so we could get a flipping behaviour

   if(engSts == 0 && (int)inputVal.StartBtn == 1) 
   {
      engSts = EngSts::On;
      setEngTrqFromAccPdl(inputVal, EngineSpeed);
   }
   else if(engSts == 1 && (int)inputVal.StartBtn == 1) 
   {
      engSts = EngSts::Off;
      
      // Kill torque instead of AccPdl and EngineSpeed
      engTrq = 0; 
   }
   else if(engSts == 1) 
   {
      setEngTrqFromAccPdl(inputVal, EngineSpeed);
   }
}

void Engine::setEngTrqFromAccPdl(canInput inputVal, float EngineSpeed)
{
   // read AcclPdl value from CAN
   // read EngineRPS from gearbox(calculated in previous loop)
   // Calculate new Trq
   // TODO: take EngSts as input

   if(inputVal.AccPdl)
   {
      engTrq = 300; // Pedal to the metal
   }
   else
   {
      engTrq = 0;
   }   
}
