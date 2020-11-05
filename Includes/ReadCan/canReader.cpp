#include <iostream>

#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp

struct canInput
    {
        int8_t BrakePdl;
        int8_t AccPdl;
        int8_t GearReq;
        int8_t StartBtn;
    };

bool canReader(canInput &out) {
    bool retval=false;
    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        return (false);
    }
    retval=true;
    while (true) {
        scpp::CanFrame fr;
        if (sockat_can.read(fr) == scpp::STATUS_OK) { 
            if(fr.id==001){
                out.BrakePdl=fr.data[0];
                out.AccPdl=fr.data[1];
                return retval;
            }  
            else if(fr.id==002){
                out.GearReq=fr.data[0];
                return retval;
            } 
            else if(fr.id==003){
                out.StartBtn=fr.data[0];
                return retval;
            }
        }
    }
    
}

int main()
{
    canInput inputVal;
    while(true)
    {
        if (canReader(inputVal))
        {
            printf("BrkPdl %d , AccPdl: %d, GearReq: %d, StartBtn: %d, \n", inputVal.BrakePdl, inputVal.AccPdl, inputVal.GearReq, inputVal.StartBtn);    
        } 
        else 
        {
            break;
        }
        
    }
    std::cout<<"Can network read error"<<std::endl;

}