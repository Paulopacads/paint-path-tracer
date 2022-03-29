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
    virtual struct NextObject intersect(Vector3, Vector3);
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
    struct NextObject intersect(Vector3, Vector3);
    bool contains(Vector3);
    Vector3 normal(Vector3);
};

class Triangle : public Object
{
public:
    Vector3 coord_a;
    Vector3 coord_b;
    Vector3 coord_c;

    Triangle(Material *, Vector3, Vector3, Vector3);
    struct NextObject intersect(Vector3, Vector3);
    Vector3 normal(Vector3);
};
