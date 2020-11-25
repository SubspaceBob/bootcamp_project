#include "input_handler.h"
#include <chrono>
#include <thread>

int main() { 
    int cycleTime = 100; // Rough Can cycletime in ms const_
    InputHandler inpHandl;
    bool stop = false;

    while (!stop)
    { 
        stop = inpHandl.run();
        std::this_thread::sleep_for(std::chrono::milliseconds(cycleTime));
    }
    return 0;
}
