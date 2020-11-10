#include "InputHandler.h"
#include <chrono>
#include <thread>

int main() {
    
    InputHandler ih;

    // while
    bool stop = false;
    while (!stop)
    { 
        stop = ih.run(250);
    }
    //
    return 0;
}