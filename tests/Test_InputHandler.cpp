#include "InputHandler.h"
#include <chrono>
#include <thread>

int main() {
    
    InputHandler ih;

    // while
    bool stop = false;
    while (!stop)
    { 
        stop = ih.run();
    }
    //
    ih.stop();
    return 0;
}