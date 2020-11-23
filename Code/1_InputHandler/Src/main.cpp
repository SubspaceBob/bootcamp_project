#include "input_handler.h"

int main() { 
    int cycleTime = 100; // Rough Can cycletime in ms const_
    InputHandler inpHandl;
    bool stop = false;

    while (!stop)
    { 
        stop = inpHandl.run(cycleTime);
    }
    return 0;
}
