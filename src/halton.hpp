#pragma once

class Halton
{
public:
    double current;
    double base;

    void init(int, int); // initialize values
    double next(); // compute Halton next sequence result
    double get(); // get current value
};
