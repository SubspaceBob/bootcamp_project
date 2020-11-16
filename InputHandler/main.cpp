#include "InputHandler.h"
#include "frameToBus.h"

int main() { 
    int cycleTime = 100; // Rough Can cycletime in ms
    InputHandler inpHandl;
    bool stop = false;

    while (!stop)
    { 
        stop = inpHandl.run(cycleTime);
    }
    return 0;
}
