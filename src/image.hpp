#pragma once

#include <string>

#include "vector3.hpp"

class Image
{
private:
    int width;
    int height;
    Vector3 *pixels;

public:
    Image(int, int);

    void setPixel(int, int, Vector3);

    Vector3 getPixel(int, int);

    int save(std::string);
};
