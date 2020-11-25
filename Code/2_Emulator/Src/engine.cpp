#include "engine.h"
#include "can_io.h"

Engine::Engine()
{
   engSts = Off;
   engTrq = 0;
   bool lastCycle = false;
}

void Engine::run(const Frame1 &frame1, const Frame3 &frame3, const Frame4 &frame4, Frame5 &frame5, const Frame6 &frame6, SharedMemory<Frame5> &frame5Mem)
{
   // Move Stop/Start code to separate function?
   // Using lastCycle for debouncing
   if(engSts == EngSts::Off && frame1.data.startBtn == 1 
      && lastCycle == false && frame3.data.brkPdl == 100) {
      // Engine off and first press = Turn on
      std::cout << "Starting engine" << std::endl;
      engSts = On;
      lastCycle = true;
   }
   else if(engSts == EngSts::On && frame1.data.startBtn == 1
      && lastCycle == false && frame6.data.gearStick == 0) {
         // Engine on and first press = Turn off
         std::cout << "Stopping engine" << std::endl;
         engSts = Off;
         lastCycle = true;
   }
   else if (frame1.data.startBtn == 1) {
      // No scenario fullfilled yet - waiting for more
   }
   else if (frame1.data.startBtn == 0)
   {
      // Nobody wants to start or shutdown the engine
      // make ready for another debounce sequence
      lastCycle = false;
   }
   else {
      // If this happens my logic is in Friday afternoon mode...
      std::cout << "Major fail in Engine On/Off" << std::endl;
      exit(EXIT_FAILURE);
   }
   
   setEngTrqFromAccPdl(frame3);

   // Store values to CANOut
   frame5Mem.write(frame5);
   
   std::cout <<" EngineStatus: " << engSts    
             <<" EngTrq: "       << engTrq   << std::endl; //*60?
}

void Engine::setEngTrqFromAccPdl(const Frame3 &frame3)
{
   // read AcclPdl value from CAN
   // read engineRPS from gearbox(calculated in previous loop)
   // Calculate new Trq
   if(frame3.data.accPdl && this->engSts== On)
   {
      engTrq = VEHICLE::MAX_TORQUE; // Pedal to the metal
   }
   else if (this->engSts== On)
      engTrq = VEHICLE::IDLE_TORQUE;   // Engine always produces torque if running
   else
      engTrq = 0;
}
