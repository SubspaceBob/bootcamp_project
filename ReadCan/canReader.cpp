#include <iostream>
#include "CanInput.h"
#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp


bool canReader(canInput &out) {
    bool retval=false;
    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        return (true);
    }
    scpp::CanFrame fr;
    if (sockat_can.read(fr) == scpp::STATUS_OK) { 
        if(fr.id==001){
            out.BrakePdl=fr.data[0];
            out.AccPdl=fr.data[1];
        }  
        else if(fr.id==002){
            out.GearReq=fr.data[0];
        } 
        else if(fr.id==003){
            out.StartBtn=fr.data[0];
            out.Ignition=fr.data[1];
        }
    }
return (retval);
}
