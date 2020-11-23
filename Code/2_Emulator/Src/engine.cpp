#include "engine.h"
#include "can_io.h"

Engine::Engine()
{
   engSts = Off;
   engTrq = 0;
}

void Engine::run(CanInput &inputVal, CanOutput &canOut, float engineSpeed, int timeStep, int gearStick)
{
   // Move Stop/Start code to separate function?

   // Using last cycle for debouncing
   if(engSts == EngSts::Off && (int)inputVal.startBtn == 1 
      && lastCycle.startBtn == 0 && (int)inputVal.brkPdl == 100) {
      // Engine off and first press = Turn on
      std::cout << "Starting engine" << std::endl;
      engSts = On;
      lastCycle.startBtn = 1;
   }
   else if(engSts == 1 && (int)inputVal.startBtn == 1 && lastCycle.startBtn == 0 && gearStick == 0 ) {
         // Engine on and first press = Turn off
         std::cout << "Stopping engine" << std::endl;
         engSts = Off;
         lastCycle.startBtn = 1;
   }
   else if ((int)inputVal.startBtn == 1) {
      // No scenario fullfilled yet - waiting for more
   }
   else if ((int)inputVal.startBtn == 0)
   {
      // Nobody wants to start or shutdown the engine
      // make ready for another debounce sequence
      lastCycle.startBtn = 0;
   }
   else {
      // If this happens my logic is in Friday afternoon mode...
      std::cout << "Major fail in Engine On/Off" << std::endl;
      exit(EXIT_FAILURE);
   }
   
   setEngTrqFromAccPdl(inputVal, engineSpeed);

   // Store values to CANOut
   canOut.engSts    = static_cast<uint8_t> (engSts);
   
   std::cout <<" EngineStatus: "    << engSts         << 
               " EngTrq: "          << engTrq         << 
               " EngSpeed[RPM]: "   << engineSpeed*60 << std::endl;
}

void Engine::setEngTrqFromAccPdl(CanInput inputVal, float engineSpeed)
{
   // read AcclPdl value from CAN
   // read engineRPS from gearbox(calculated in previous loop)
   // Calculate new Trq
   if(inputVal.accPdl && this->engSts== On)
   {
      engTrq = VEHICLE::MAX_TORQUE; // Pedal to the metal
   }
   else if (this->engSts== On)
      engTrq = VEHICLE::IDLE_TORQUE;   // Engine always produces torque if running
   else
      engTrq = 0;
}
