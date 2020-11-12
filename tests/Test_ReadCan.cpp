#include <iostream>
#include "CanInput.h"
#include "socketcan_cpp.h"
#include <thread>

bool canReader(canInput &out);


int main()
{   
    canInput inputVal;
    bool error;
    while (true)
    {
        error=canReader(inputVal);
        printf("%d %d %d   \n", inputVal.AccPdl, inputVal.BrakePdl, inputVal.GearReq);
         std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}