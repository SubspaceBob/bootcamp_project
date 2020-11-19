#include <iostream>
#include <chrono>
#include <thread>
#include "../Include/input_handler.h"

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
            break;
        case 10: //btn 1 = hazard button
            if (data.ttByte1.telltales1.hazard==1 && key.second==1)
                data.ttByte1.telltales1.hazard=0;
            else if (data.ttByte1.telltales1.hazard==0 && key.second==1)
            {
                data.ttByte1.telltales1.hazard=1;
            }
            break;
        case 11: //btn 2
            if (data.ttByte1.telltales1.left_blinker==1 && key.second==1)
                data.ttByte1.telltales1.left_blinker=0;
            else if (data.ttByte1.telltales1.left_blinker==0 && key.second==1)
            {
                data.ttByte1.telltales1.left_blinker=1;
            }
            break;
        case 12: //btn 3
            if (data.ttByte1.telltales1.engine_check==1 && key.second==1)
                data.ttByte1.telltales1.engine_check=0;
            else if (data.ttByte1.telltales1.engine_check==0 && key.second==1)
            {
                data.ttByte1.telltales1.engine_check=1;
            }
            break;
        case 13: //btn 4
            if (data.ttByte1.telltales1.oil_check==1 && key.second==1)
                data.ttByte1.telltales1.oil_check=0;
            else if (data.ttByte1.telltales1.oil_check==0 && key.second==1)
            {
                data.ttByte1.telltales1.oil_check=1;
            }
            break;
        case 14: //btn 5
            if (data.ttByte1.telltales1.abs==1 && key.second==1)
                data.ttByte1.telltales1.abs=0;
            else if (data.ttByte1.telltales1.abs==0 && key.second==1)
            {
                data.ttByte1.telltales1.abs=1;
            }
            break;
        case 15: //btn 6
            if (data.ttByte1.telltales1.battery==1 && key.second==1)
                data.ttByte1.telltales1.battery=0;
            else if (data.ttByte1.telltales1.battery==0 && key.second==1)
            {
                data.ttByte1.telltales1.battery=1;
            }
            break;
        case 16: //btn 7
            if (data.ttByte1.telltales1.seat_belt==1 && key.second==1)
                data.ttByte1.telltales1.seat_belt=0;
            else if (data.ttByte1.telltales1.seat_belt==0 && key.second==1)
            {
                data.ttByte1.telltales1.seat_belt=1;
            }
            break;
        case 17: //btn 8
            if (data.ttByte2.telltales2.doors_open==1 && key.second==1)
                data.ttByte2.telltales2.doors_open=0;
            else if (data.ttByte2.telltales2.doors_open==0 && key.second==1)
            {
                data.ttByte2.telltales2.doors_open=1;
            }
            break;
        case 18: //btn 9
            if (data.ttByte2.telltales2.high_beam==1 && key.second==1)
                data.ttByte2.telltales2.high_beam=0;
            else if (data.ttByte2.telltales2.high_beam==0 && key.second==1)
            {
                data.ttByte2.telltales2.high_beam=1;
            }
            break;
        case 19: //btn 0
            if (data.ttByte2.telltales2.hand_break==1 && key.second==1)
                data.ttByte2.telltales2.hand_break=0;
            else if (data.ttByte2.telltales2.hand_break==0 && key.second==1)
            {
                data.ttByte2.telltales2.hand_break=1;
            }
            break;
        case 20: //btn +
            if (data.ttByte1.telltales1.right_blinker==1 && key.second==1)
                data.ttByte1.telltales1.right_blinker=0;
            else if (data.ttByte1.telltales1.right_blinker==0 && key.second==1)
            {
                data.ttByte1.telltales1.right_blinker=1;
            }
            break;

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
    canIO.frameToBus((uint8_t)6, (uint8_t)data.ttByte1.canByte, (uint8_t)data.ttByte2.canByte);
    
    // Wait CAN cycletime
    std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
    
    return exitLoop; 
}
