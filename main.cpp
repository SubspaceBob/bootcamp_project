#include <iostream>
#include <thread>

void rdCan(canInput &out);
void virtCar(/*TODO: Pass arguments*/ /*pointer to common memory, */ class Engine, class GearBox);

int main(){
    // TODO: Initalize objects engine and gearbox and set their initvalues,
    // once the classes are ready in order to keep track of the current 
    // status between cycles.
    class Engine engine;
    class GearBox gearbox;

    // TODO: Initiate a memorypointer so that rdCAN & virtCar can operate on
    // same memory location
    canInput *memPtr;

    // Init two threads, one for running an eternal CANread thread,
    // another one for running an eternal virtCar thread. 
    // (Unless gracefully shut down by IgniotionOff signal).
    // Pass memPtr to both and Engine and Gearboxobject to virtCar
    

    std::thread rdCan (rdCan, memPtr);
    std::thread virtCar (virtCar, memPtr, &engine, &gearbox);

    delete memPtr;
    return 0;
}