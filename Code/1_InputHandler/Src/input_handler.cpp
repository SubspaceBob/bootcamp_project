#include <iostream>
#include "../Include/input_handler.h"

InputHandler::InputHandler(){
    std::cout << "Hello there!" << std::endl;
    canIO.start_can();
    reader.start();
} 

void InputHandler::writeToCan() {
    //copy data to parent data
    canIO.frame1.write(canIO.frame1);
    canIO.frame2.write(canIO.frame2);
    canIO.frame3.write(canIO.frame3);
    canIO.frame4.write(canIO.frame4);
    //Output the frames
    canIO.frameToBus(canIO.frame1);
    canIO.frameToBus(canIO.frame2);
    canIO.frameToBus(canIO.frame3);
    canIO.frameToBus(canIO.frame4);
}

bool InputHandler::run(){
    bool exitLoop = false;

    KeyInput key = reader.getKey();
    std::cout << "KeyPress: " << key.first << "  "<< key.second << std::endl;

    //Ordered according to functionality/Frames
    switch(key.first){ 
        case 0: break; // No buttons pressed = Do nothing     
        case 9: exitLoop = true; break; // Escape = Exit inputHandler
//______Frame1_startBtn,_Quitbtn,_Battery_telltale______________________________
        case 36: canIO.frame1.data.startBtn = (uint8_t) key.second; break; // Enter = startBtn
        case 24: canIO.frame1.data.quitEmul = key.second; break; // Q = quitEmul
        case 15: // btn 6 = battery telltale
            if (key.second == 1) {
                if (canIO.frame1.data.flagByte.flags.battery == 0)
                    canIO.frame1.data.flagByte.flags.battery = 1;
                else canIO.frame1.data.flagByte.flags.battery = 0;
            } break;
//______Frame2_Hazard,_blinkers_&_High_beam_telltale____________________________
        case 10: //btn 1 = hazard button
            if (key.second == 1) {
                if (canIO.frame2.data.flagByte.flags.hazard==0)
                    canIO.frame2.data.flagByte.flags.hazard = 1;
                else canIO.frame2.data.flagByte.flags.hazard = 0; 
            } break;
        case 11: //btn 2 = left blinker
            if (key.second == 1) {
                if (canIO.frame2.data.flagByte.flags.left_blinker == 0)
                    canIO.frame2.data.flagByte.flags.left_blinker = 1;
                else canIO.frame2.data.flagByte.flags.left_blinker = 0; 
            } break;
        case 20: //btn + = right blinker
            if (key.second == 1) {
                if (canIO.frame2.data.flagByte.flags.right_blinker == 0)
                    canIO.frame2.data.flagByte.flags.right_blinker = 1;
                else canIO.frame2.data.flagByte.flags.right_blinker = 0;
            } break;
        case 18: //btn 9 = high beam
            if (key.second == 1) {
                if (canIO.frame2.data.flagByte.flags.high_beam == 0)
                    canIO.frame2.data.flagByte.flags.high_beam=1;
                else canIO.frame2.data.flagByte.flags.high_beam=0;
            } break;
//______Frame3_BrkPdl,_AccPdl,_Handbrake_&_ABS_telltale_______________________
        case 116: // Down Arrow = Brake
            // TODO: Implement logic for making this signal analog
            if (key.second == 1) canIO.frame3.data.brkPdl = 100;
            else canIO.frame3.data.brkPdl = 0;
            break;
        case 111: // Up Arrow = Accelerate
            // TODO: Implement logic for making this signal analog
            if (key.second == 1) canIO.frame3.data.accPdl = 100;
            else canIO.frame3.data.accPdl = 0; 
            break;
        case 19: // btn 0 = hand_brake
            if (key.second == 1) {
                if (canIO.frame3.data.flagByte.flags.hand_brake == 0)
                    canIO.frame3.data.flagByte.flags.hand_brake = 1;
            else canIO.frame3.data.flagByte.flags.hand_brake =0;
            } break;
        case 14: //btn 5 = ABS
            if (key.second==1) {
                /*if (frame3.data.flagByte.flags.abs == 0)
                    frame3.data.flagByte.flags.abs = 1;
                else frame3.data.flagByte.flags.abs = 0;*/
            } break;
//______Frame4_GearReq,_seat_belt_&_doors_open_telltales______________________
//__________GearReq_Toggles_depending_on_buttons_P,_R,_N,_D,_NoReq________________
        case 33: // P = Park 
            if (key.second == 1) canIO.frame4.data.gearReq = 0;
            else canIO.frame4.data.gearReq = 4;   
            break;
        case 27: // R = Reverse
            if (key.second == 1) canIO.frame4.data.gearReq = 1;
            else canIO.frame4.data.gearReq = 4;   
            break;   
        case 57: // N = Neutral
            if (key.second == 1) canIO.frame4.data.gearReq = 2;
            else canIO.frame4.data.gearReq = 4;   
            break;
        case 40: // D = Drive
            if (key.second == 1) canIO.frame4.data.gearReq = 3;
            else canIO.frame4.data.gearReq = 4;   
            break;
        case 16: // btn 7 = seat_belt telltale
            if (key.second == 1) {
                if (canIO.frame4.data.flagByte.flags.seat_belt == 0)
                    canIO.frame4.data.flagByte.flags.seat_belt = 1;
                else canIO.frame4.data.flagByte.flags.seat_belt = 0;
            } break;
        case 17: // btn 8 = doors_open telltale
            if (key.second == 1) {
                if (canIO.frame4.data.flagByte.flags.doors_open == 0)
                    canIO.frame4.data.flagByte.flags.doors_open = 1;
                else canIO.frame4.data.flagByte.flags.doors_open = 0;
            } break;
//______Unused_buttons________________________________________________________
        default: // Unexpected buttons are ignored for now
            // Uncommenting this will make the program intentionally crash with a fault
            // message needed for fault tracing
            /*std::cout << "The key.first switch case generated an unvalid scenario" << std::endl;
            std::cout << "Value is: " << key.first << std::endl;
            exit(EXIT_FAILURE);*/
            break;
    } 

    writeToCan();
    
    return exitLoop; 
}
