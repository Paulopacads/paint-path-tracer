#include "halton.hpp"

void Halton::init(int index, int base)
{
    this->base = base;
    double f = 1;
    double r = 0;
    while (index > 0)
    {
        f /= base;
        r += f * (index % base);
        index /= base;
    }
    this->current = r;
}

// Compute Halton next sequence result based on Wikipedia algorithm 
void Halton::next()
{
    double r = 1. - current - 1e-6;
    double ibase = 1. / base;

    if (ibase < r)
        current += ibase;
    else
    {
        double t = ibase;
        double t2 = t * ibase;
        while (t2 >= r)
        {
            t = t2;
            t2 *= ibase;
        }

        current += t + t2 - 1;
    }
}

double Halton::get()
{
    return this->current;
}
