#include "InputHandler.h"
#include "KeyboardReader.h"
#include <unistd.h>
#include <chrono>
#include <thread>
/*void InterpretKey(int key){

} */

int main() {
    
    // send greetings to user :)

    user_input_signals data;
    unsigned int sleep_us = 100000; // 10000 = 10 ms

    std::cout << "Hello there!" << std::endl;

    // create CANWriter object
    // CANWriter.start()
    
    // create and start KeyboardReader
    KeyboardReader reader;
    reader.start();

    // while
    std::pair<int, int> key;
    while (key.first != 0x09) // Escape is not Quit(graceful shutdown)
    { 
        /* Get user input and intepret */
        key = reader.getKey();
        
        std::cout << "KeyPress: " << key.first << "  "<< key.second << std::endl;
 
        switch(key.first){ 
            // toggle these on Press/Release
            case 0x62   : data.AccPdl   = key.second;  break; // 0x62 = Up-button = Accelerate
            case 0x68   : data.BrkPdl   = key.second;  break; // 0x68 = Down-button = Decelerate
            case 0x24   : data.StartBtn = key.second;  break; // 0x24 = Enter = startbutton 
            case 0x18   : data.Ignition = key.second;  break;// 0x18 = Q = quitbutton?
        
            // Change GearRequest when a new GearRequest button is pressed 
            case 0x21   : data.GearReq = 1; break;// Request P = 1 ??
            case 0x1b   : data.GearReq = 2; break;// Request R = 2 ??
            case 0x39   : data.GearReq = 3; break;// Request N = 3 ??
            case 0x28   : data.GearReq = 4; break;// Request D = 4 ??
            //default     : data.GearReq = 0; // No request // 
            
        }       
        
        // STUBBED send on CAN
        std::cout << "frameToBus(1, BrkPdl="   << (int)data.BrkPdl   << ", AccPdl="   << (int)data.AccPdl <<")"    << std::endl;
        std::cout << "frameToBus(2, GearReq="  << (int)data.GearReq  <<")"                                   << std::endl;
        std::cout << "frameToBus(3, StartBtn=" << (int)data.StartBtn << ", Ignition=" << (int)data.Ignition <<")"  << std::endl;
    
        // check if KeyInput is graceful shutdown
        //      terminate()
        //      break;
        //sleep 10 ms
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }
    //
    reader.stop();
    // CANWriter.stop();
    // delete CANWriter;
    return 0;
         
}