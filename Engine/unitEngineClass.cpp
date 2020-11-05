#include <iostream>
#include <cassert>
#include "engine.h"

int main(){
    Engine testEngine;

    // Test init values and getters
    assert (testEngine.getEngSts() == On);
    assert (testEngine.getEngTrq() == 300);

    // Test engSts setter   
    testEngine.setEngSts(Off);
    assert (testEngine.getEngSts() == Off);

    // Test enqTrq setter and its boundaries
    // TODO: Change first 2 asserts to 0 once stub for always on is removed.
    testEngine.setEngTrq(-1);
    assert (testEngine.getEngTrq() == 300); //Invalid input, keep last value
    testEngine.setEngTrq(-32768);
    assert (testEngine.getEngTrq() == 300); //Invalid input, keep last value

    testEngine.setEngTrq(0);
    assert (testEngine.getEngTrq() == 0);

    testEngine.setEngTrq(300);
    assert (testEngine.getEngTrq() == 300);
    
    testEngine.setEngTrq(301);
    assert (testEngine.getEngTrq() == 300); //Invalid input, keep last value

    std::cout << "The unit tests for the EngineClass have passed" << std::endl;

    return 0;
}