#ifndef frameToBus_h
#define frameToBus_h
#include <iostream>
#include "../Includes/socketcan_cpp/socketcan_cpp.h"

void frameToBus(uint8_t frameNo, uint8_t signalValue);
void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint8_t signal2Value);
void frameToBus(uint8_t frameNo, uint8_t signal1Value, uint16_t signal2Value);

#endif