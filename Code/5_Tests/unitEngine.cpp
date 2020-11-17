#include <iostream>
#include <cassert>
#include "../Headerfiles/engine.h"
#include "../Headerfiles/can_io.h"

int main(){
    Engine testEngine;
    CanInput inputVal;
    float EngineSpeed = 0; // TODO: No logic implemented yet
    int TimeStep = 10;

    // Test init values and getters
    assert (testEngine.getEngSts() == Off);
    assert (testEngine.getEngTrq() == 0);

    // Test run function with init values no btnpress
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off);
    assert (testEngine.getEngTrq() == 0);

    // Test engine on
    inputVal.startBtn = 1;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off && testEngine.getEngTrq() == 0);

    inputVal.startBtn = 0;
    inputVal.brkPdl = 100;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off && testEngine.getEngTrq() == 0);

    inputVal.startBtn = 1;
    inputVal.brkPdl = 100;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    // Test engine Off
    inputVal.startBtn = 1;
    inputVal.gearReq = 1;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.startBtn = 1;
    inputVal.gearReq = 2;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.startBtn = 1;
    inputVal.gearReq = 3;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.startBtn = 0;
    inputVal.gearReq = 4;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.startBtn = 1;
    inputVal.gearReq = 4;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off && testEngine.getEngTrq() == 0);

    std::cout << "The unit tests for the EngineClass have passed" << std::endl;

    return 0;
}