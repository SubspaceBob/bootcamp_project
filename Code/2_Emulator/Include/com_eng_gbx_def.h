#ifndef COMENGGBXDEF_H
#define COMENGGBXDEF_H
#include <iostream>     
    
/* This file contains some of the definitions that 
   both engine and gearbx needs to now about.
   By placing them here we avoid circular arguments
   where gearbox includes engine and engine includes 
   gearbox. */
   
// Owned by engine
enum EngSts : uint8_t {Off, On};
typedef uint16_t Trq; 

//Owned by gbx
enum class GearPattern: int8_t {
    P, R, N, D
};

#endif