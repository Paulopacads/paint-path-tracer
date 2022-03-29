#pragma once

#include "vector3.hpp"

class Camera
{
public:
    Vector3 center;
    Vector3 up;
    Vector3 right;
    Vector3 direction;
    double alphaFOV;
    double betaFOV;
    double distance;

    Camera(Vector3, Vector3, Vector3, double, double, double);
};
