#include <iostream>
#include "can_io.h"
#include "socketcan_cpp.h"
#include <thread>

bool canReader(CanInput &out);


int main()
{   
    CanInput inputVal;
    bool error;
    while (true)
    {
        error=canReader(inputVal);
        printf("%d %d %d   \n", inputVal.accPdl, inputVal.brkPdl, inputVal.gearReq);
         std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}