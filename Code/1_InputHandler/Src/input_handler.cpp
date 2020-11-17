#include <iostream>
#include <chrono>
#include <thread>
#include "input_handler.h"

InputHandler::InputHandler(){
    std::cout << "Hello there!" << std::endl;
    canIO.start_can();
    reader.start();
} 

bool InputHandler::run(int cycleTime){
    bool exitLoop = false;

    KeyInput key = reader.getKey();
    std::cout << "KeyPress: " << key.first << "  "<< key.second << std::endl;

    //Ordered according to functionality/Frames
    switch(key.first){ 
        case 0: break; // No buttons pressed = Do nothing     
        case 9: // Escape = Exit program
            // TODO: Implement a gracefull shutdown see also Q button
            // Stop eternal main loop
            exitLoop = true;
            break;
        
        // Frame1
        case 116: // Down Arrow = Brake
            // TODO: Implement logic for making this signal analog
            if (key.second == 0) data.brkPdl = 0;
            else data.brkPdl = 100;
            break;
        case 111: // Up Arrow = Accelerate
            // TODO: Implement logic for making this signal analog
            if (key.second == 0) data.accPdl = 0;
            else data.accPdl = 100; 
            break; 
    
        // Frame 2 // Toggles depending on buttons P,R,N,D = GearStickRequest
        // GearReq = 4 is NoRequest
        case 33: // Park 
            if (key.second == 1) data.gearReq = 0;
            else data.gearReq = 4;   
            break;
        case 27: // Reverse
            if (key.second == 1) data.gearReq = 1;
            else data.gearReq = 4;
            break;   
        case 57: // Neutral
            if (key.second == 1) data.gearReq = 2;
            else data.gearReq = 4;   
            break;
        case 40: // Drive
            if (key.second == 1) data.gearReq = 3;
            else data.gearReq = 4;   
            break;
    
        // Frame 3 Enter = Start button
        case 36: data.startBtn = key.second; break;
        case 24: //Q = quitbutton
            data.quitEmul = key.second; break;
            // TODO: Possibly connected in gracefull shutdown see also escape button
        
        // Unused buttons
        default: // Unexpected buttons ignored for now
            /*std::cout << "The key.first switch case generated an unvalid scenario" << std::endl;
            std::cout << "Value is: " << key.first << std::endl;
            exit(EXIT_FAILURE);*/
            break;  
    } 

    //Output the frames
    canIO.frameToBus((uint8_t)1, (uint8_t)data.brkPdl, (uint8_t)data.accPdl);
    canIO.frameToBus((uint8_t)2, (uint8_t)data.gearReq);
    canIO.frameToBus((uint8_t)3, (uint8_t)data.startBtn, (uint8_t)data.quitEmul);
    
    // Wait CAN cycletime
    std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
    
    return exitLoop; 
}
