#pragma once

#include "material.hpp"
#include "vector3.hpp"

struct NextObject;

class Object
{
public:
    Material *material;

    Object(Material *);
    virtual ~Object() = 0;
    virtual double intersect(Vector3, Vector3);
    virtual bool contains(Vector3);
    virtual Vector3 normal(Vector3);
    virtual struct MaterialInfo getMaterialInfo(Vector3);
};

class Sphere : public Object
{
public:
    Vector3 center;
    double radius;

    Sphere(Material *, Vector3, double);
    double intersect(Vector3, Vector3);
    bool contains(Vector3);
    Vector3 normal(Vector3);
};

class Plane : public Object
{
public:
    Vector3 norm;
    double d;

    Plane(Material *, Vector3, double);
    double intersect(Vector3, Vector3);
    Vector3 normal(Vector3);
};
