#include <iostream>
#ifndef CANINPUT_H
#define CANINPUT_H


struct canInput
    {
        int8_t BrakePdl;
        int8_t AccPdl;
        int8_t GearReq;
        int8_t StartBtn;
        int8_t Ignition;

        canInput() {BrakePdl=0; AccPdl=0; GearReq=0; StartBtn=0; Ignition=0;}
    };
#endif