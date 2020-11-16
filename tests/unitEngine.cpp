#include <iostream>
#include <cassert>
#include "engine.h"
#include "CanInput.h"

int main(){
    Engine testEngine;
    canInput inputVal;
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
    inputVal.StartBtn = 1;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off && testEngine.getEngTrq() == 0);

    inputVal.StartBtn = 0;
    inputVal.BrakePdl = 100;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off && testEngine.getEngTrq() == 0);

    inputVal.StartBtn = 1;
    inputVal.BrakePdl = 100;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    // Test engine Off
    inputVal.StartBtn = 1;
    inputVal.GearReq = 1;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.StartBtn = 1;
    inputVal.GearReq = 2;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.StartBtn = 1;
    inputVal.GearReq = 3;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.StartBtn = 0;
    inputVal.GearReq = 4;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == On && testEngine.getEngTrq() == 300);

    inputVal.StartBtn = 1;
    inputVal.GearReq = 4;
    testEngine.run(inputVal, EngineSpeed, TimeStep);
    assert (testEngine.getEngSts() == Off && testEngine.getEngTrq() == 0);

    std::cout << "The unit tests for the EngineClass have passed" << std::endl;

    return 0;
}