#pragma once

#include "vector3.hpp"

// camera for a scene
class Camera
{
public:
    Vector3 center; // position
    Vector3 up; // for rotation
    Vector3 right;
    Vector3 direction; // vector forward
    double alphaFOV;
    double betaFOV;
    double distance; // distance between center and proj. plane

    Camera(Vector3, Vector3, Vector3, double, double, double);
};
