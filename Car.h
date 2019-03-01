//#pragma once
#include "Wheel.h"  // Include Wheel's definition so it can be used in Car.
#include <vector>

extern int var;

class Car
{
    void foo();
    std::vector<Wheel> wheels;
};