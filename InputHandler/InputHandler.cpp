#include <iostream>
#include <chrono>
#include <thread>
#include "InputHandler.h"

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
                if (key.second == 0) data.BrakePdl = 0;
                else data.BrakePdl = 100;
            break;
        case 111: // Up Arrow = Accelerate
            // TODO: Implement logic for making this signal analog
                if (key.second == 0) data.AccPdl = 0;
                else data.AccPdl = 100; 
            break; 
    // Frame 2 // Toggles depending on buttons P,R,N,D = GearStickRequest
        case 33: data.GearReq = 0; break;
        case 27: data.GearReq = 1; break;
        case 57: data.GearReq = 2; break;
        case 40: data.GearReq = 3; break;
    // Frame 3 Enter = Start button
        case 36: data.StartBtn = key.second; break;
        case 24: //Q = quitbutton
            data.Ignition = key.second; break;
            // TODO: Possibly connected in gracefull shutdown see also escape button
            break;
    // Unused buttons
        default: // Unexpected buttons ignored for now
            /*std::cout << "The key.first switch case generated an unvalid scenario" << std::endl;
            std::cout << "Value is: " << key.first << std::endl;
            exit(EXIT_FAILURE);*/
            break;  
    } 

    //Output the frames
    canIO.frameToBus((uint8_t)1, (uint8_t)data.BrakePdl, (uint8_t)data.AccPdl);
    canIO.frameToBus((uint8_t)2, (uint8_t)data.GearReq);
    canIO.frameToBus((uint8_t)3, (uint8_t)data.StartBtn, (uint8_t)data.Ignition);
    
    // Wait CAN cycletime
    std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
    
    return exitLoop; 
}
