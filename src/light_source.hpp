#pragma once

#include "vector3.hpp"

class LightSource
{
public:
    Vector3 position;
    Vector3 color;
    double lightness;

    LightSource(Vector3, Vector3, double);
};

class PointLightSource : public LightSource
{
public:
    PointLightSource(Vector3, Vector3, double);
};

class SphereLightSource : public LightSource
{
public:
    double radius;

    SphereLightSource(Vector3, Vector3, double, double);
};
