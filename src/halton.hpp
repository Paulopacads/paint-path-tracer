#pragma once

class Halton
{
public:
    double current;
    double base;

    void init(int, int);
    void next();
    double get();
};
