#include "InputHandler.h"
#include "../SendCan/frameToBus.h"

int main() { 
    int cycleTime = 250; // Rough Can cycletime in ms
    InputHandler inpHandl;
    bool stop = false;

    while (!stop)
    { 
        stop = inpHandl.run(cycleTime);
    }
    return 0;
}
